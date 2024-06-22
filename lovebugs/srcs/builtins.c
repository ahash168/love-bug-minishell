/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahashem <ahashem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 14:02:43 by bgordag           #+#    #+#             */
/*   Updated: 2024/06/22 12:25:39 by ahashem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	builtin_input(char *input)
{
	int	builtin;

	builtin = 1;
	if (ft_strncmp(input, "echo", 4) == 0 || ft_strncmp(input, "cd", 2) == 0
	|| ft_strncmp(input, "pwd", 3) == 0 || ft_strncmp(input, "export", 6) == 0
	|| ft_strncmp(input, "unset", 5) == 0 || ft_strncmp(input, "env", 3) == 0
	|| ft_strncmp(input, "exit", 4) == 0)
		builtin = 0;
	return (builtin);
}

int	exec_builtin(char **input, t_env *env)
{
	(void) env;
	if (ft_strncmp(input[0], "echo", 4) == 0)
		ft_echo(input);
	// else if (ft_strncmp(input[0], "cd", 2) == 0)
	// 	ft_cd(input, env);
	else if (ft_strncmp(input[0], "pwd", 3) == 0)
		ft_pwd();
	// else if (ft_strncmp(input[0], "export", 6) == 0)
	// 	ft_export();
	// else if (ft_strncmp(input[0], "unset", 5) == 0)
	// 	ft_unset();
	// else if (ft_strncmp(input[0], "env", 3) == 0)
	// 	ft_env(env);
	// else if (ft_strncmp(input[0], "exit", 4) == 0)
	// 	ft_exit();
	else
		return (1);
	return (0);
}
