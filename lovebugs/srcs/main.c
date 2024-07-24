/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahashem <ahashem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 12:34:07 by ahashem           #+#    #+#             */
/*   Updated: 2024/07/24 19:50:18 by ahashem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	main(int ac, char **av, char **env)
{
	t_mini	*shell;

	(void) av;
	if (ac != 1 || !*env)
		return (1);
	shell = ft_calloc(1, sizeof(t_mini));
	init_shell(shell);
	init_env(env, &(shell->env_list), shell);
	while (1)
	{
		shell->input = readline("minishell> ");
		if (!shell->input)
			break ;
		if (*shell->input && !ft_strset(shell->input, " \t"))
		{
			add_history(shell->input);
			if (!parsing(shell))
			{
				execution(shell);
			}
			reset_shell(shell);
		}
	}
	free_shell(shell);
	return (0);
}
