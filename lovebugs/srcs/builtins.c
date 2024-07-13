/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahashem <ahashem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 14:02:43 by bgordag           #+#    #+#             */
/*   Updated: 2024/07/13 22:42:56 by ahashem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../builtins/builtins.h"

int	is_builtin(char *cmd)
{
	int	builtin;

	builtin = 1;
	if (ft_strncmp(cmd, "echo", 4) == 0 || ft_strncmp(cmd, "cd", 2) == 0 \
	|| ft_strncmp(cmd, "pwd", 3) == 0 || ft_strncmp(cmd, "export", 6) == 0 \
	|| ft_strncmp(cmd, "unset", 5) == 0 || ft_strncmp(cmd, "env", 3) == 0 \
	|| ft_strncmp(cmd, "exit", 4) == 0 || ft_strncmp(cmd, "ECHO", 4) == 0\
	|| ft_strncmp(cmd, "PWD", 3) == 0 || ft_strncmp(cmd, "ENV", 3) == 0)
		builtin = 0;
	return (builtin);
}

int	exec_builtin(char **cmd_arg, t_env *env)
{
	// (void) env;
	if (ft_strncmp(cmd_arg[0], "echo", 4) == 0 \
	|| ft_strncmp(cmd_arg[0], "ECHO", 4) == 0)
		ft_echo(cmd_arg);
	else if (ft_strncmp(cmd_arg[0], "cd", 2) == 0)
		ft_cd(cmd_arg, env);
	else if (ft_strncmp(cmd_arg[0], "pwd", 3) == 0 \
	|| ft_strncmp(cmd_arg[0], "PWD", 3) == 0)
		ft_pwd();
	// else if (ft_strncmp(cmd_arg[0], "export", 6) == 0)
	// 	ft_export();
	// else if (ft_strncmp(cmd_arg[0], "unset", 5) == 0)
	// 	ft_unset();
	else if (ft_strncmp(cmd_arg[0], "env", 3) == 0 \
	|| ft_strncmp(cmd_arg[0], "ENV", 3) == 0)
		ft_env(env);
	// else if (ft_strncmp(cmd_arg[0], "exit", 4) == 0)
	// 	ft_exit();
	else
		return (1);
	return (0);
}
