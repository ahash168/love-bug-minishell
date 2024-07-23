/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahashem <ahashem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 14:02:43 by bgordag           #+#    #+#             */
/*   Updated: 2024/07/22 18:03:12 by ahashem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../builtins/builtins.h"

int	is_builtin(char *cmd)
{
	int	builtin;

	builtin = 1;
	if (ft_strncmp(cmd, "echo", 5) == 0 || ft_strncmp(cmd, "cd", 3) == 0 \
	|| ft_strncmp(cmd, "pwd", 4) == 0 || ft_strncmp(cmd, "export", 7) == 0 \
	|| ft_strncmp(cmd, "unset", 6) == 0 || ft_strncmp(cmd, "env", 4) == 0 \
	|| ft_strncmp(cmd, "exit", 5) == 0 || ft_strncmp(cmd, "ECHO", 5) == 0\
	|| ft_strncmp(cmd, "PWD", 4) == 0 || ft_strncmp(cmd, "ENV", 4) == 0)
		builtin = 0;
	return (builtin);
}

int	exec_builtin(t_mini *shell, t_cmd *cmds)
{
	// (void) env;
	if (ft_strncmp(cmds->cmd[0], "echo", 5) == 0 \
	|| ft_strncmp(cmds->cmd[0], "ECHO", 5) == 0)
		ft_echo(cmds->cmd);
	else if (ft_strncmp(cmds->cmd[0], "cd", 3) == 0)
		ft_cd(cmds->cmd, shell->env_list);
	else if (ft_strncmp(cmds->cmd[0], "pwd", 4) == 0 \
	|| ft_strncmp(cmds->cmd[0], "PWD", 4) == 0)
		ft_pwd();
	// else if (ft_strncmp(cmds->cmd[0], "export", 7) == 0)
	// 	ft_export();
	// else if (ft_strncmp(cmds->cmd[0], "unset", 6) == 0)
	// 	ft_unset();
	else if (ft_strncmp(cmds->cmd[0], "env", 4) == 0 \
	|| ft_strncmp(cmds->cmd[0], "ENV", 4) == 0)
		ft_env(shell->env_list);
	// else if (ft_strncmp(cmds->cmd[0], "exit", 5) == 0)
	// 	ft_exit();
	else
		return (1);
	return (0);
}
