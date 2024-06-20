/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahashem <ahashem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 12:34:07 by ahashem           #+#    #+#             */
/*   Updated: 2024/06/20 11:38:26 by ahashem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void handle_command(char *input) {
    if (strcmp(input, "exit") == 0) {
        exit(0);
    } else if (strncmp(input, "cd", 2) == 0) {
        char *path = input + 3; // Skip the "cd " part
        if (chdir(path) != 0) {
            perror("minishell");
        }
    } else if (strncmp(input, "echo", 4) == 0) {
        char *message = input + 5; // Skip the "echo " part
        printf("%s\n", message);
    } else {
        // Handle external commands
        pid_t pid = fork();
        if (pid == 0) {
            // Child process
            char *argv[] = { "/bin/sh", "-c", input, NULL };
            if (execve("/bin/sh", argv, NULL) == -1) {
                perror("minishell");
                exit(EXIT_FAILURE);
            }
        } else if (pid < 0) {
            // Error forking
            perror("minishell");
        } else {
            // Parent process
            int status;
            waitpid(pid, &status, 0);
        }
    }
}

int main() {
    char *input;
    while (1) {
        input = readline("minishell> ");
        if (!input) {
            break; // Handle EOF (Ctrl+D)
        }
        if (*input) {
            add_history(input);
			handle_command(input);
            // Parse and execute input
        }
        free(input);
    }
    return 0;
}
