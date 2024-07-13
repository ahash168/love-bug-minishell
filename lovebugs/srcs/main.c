/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahashem <ahashem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 12:34:07 by ahashem           #+#    #+#             */
/*   Updated: 2024/07/13 20:33:08 by ahashem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	main(int ac, char **av, char **env)
{
	char	*input;
	t_env	*my_env;
	t_cmd	*cmds;

	(void) av;
	if (ac != 1 || !*env)
		return (1);
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
			exec_cmds(cmds, my_env);
			// printf("HI\n");
		}
		free(input);
	}
	// freeer(my_env);
	return (0);
}
