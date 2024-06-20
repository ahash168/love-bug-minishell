/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgordag <bgordag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 12:34:07 by ahashem           #+#    #+#             */
/*   Updated: 2024/06/20 14:03:29 by bgordag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**init_env(char **env)
{
	return (arrcopy(env));
}

int main(int ac, char **av, char **env)
{
	char *input;
	char **our_env;
	
	(void) ac;
	(void) av;
	our_env = init_env(env);
    while (1) {
        input = readline("minishell> ");
        if (!input) {
            break; // Handle EOF (Ctrl+D)
        }
        if (*input) {
            add_history(input);
			if (builtin_input(input) == 0)
				exec_builtin(input, our_env);
            // Parse and execute input
        }
        free(input);
    }
	freeer(our_env);
    return (0);
}
