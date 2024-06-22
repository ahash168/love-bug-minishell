/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahashem <ahashem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 12:34:07 by ahashem           #+#    #+#             */
/*   Updated: 2024/06/22 12:17:18 by ahashem          ###   ########.fr       */
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
	char **split_input;
	
	(void) ac;
	(void) av;
	our_env = init_env(env);
	split_input = NULL;
    while (1) {
        input = readline("minishell> ");
        if (!input) {
            break; // Handle EOF (Ctrl+D)
        }
        if (*input) {
            add_history(input);
			split_input = ft_split(input, ' ');
			if (builtin_input(split_input[0]) == 0)
				exec_builtin(split_input, our_env);
            // Parse and execute input
        }
        free(input);
    }
	freeer(our_env);
    return (0);
}
