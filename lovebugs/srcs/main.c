/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahashem <ahashem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 12:34:07 by ahashem           #+#    #+#             */
/*   Updated: 2024/07/12 22:56:53 by ahashem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	main(int ac, char **av, char **env)
{
	char	*input;
	t_env	*my_env;
	t_cmd	*cmds;

	(void) ac;
	(void) av;
	my_env = NULL;
	cmds = NULL;
	init_env(env, &my_env);
	while (1)
	{
		input = readline("minishell> ");
		if (!input)
			break ;
		if (*input)
		{
			add_history(input);
			cmds = parsing(input);
			(void) cmds;
			// parsed_commands = parser(input);
			// execute_commands(parsed_commands, my_env);
			// Parse and execute input
		}
		free(input);
	}
	// freeer(my_env);
	return (0);
}
