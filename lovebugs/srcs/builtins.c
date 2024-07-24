/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: busragordag <busragordag@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 14:02:43 by bgordag           #+#    #+#             */
/*   Updated: 2024/07/22 00:06:33 by busragordag      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

int	exec_builtin(t_mini *shell)
{
	// (void) env;
	if (ft_strncmp(shell->cmds->cmd[0], "echo", 5) == 0 \
	|| ft_strncmp(shell->cmds->cmd[0], "ECHO", 5) == 0)
		ft_echo(shell->cmds->cmd);
	else if (ft_strncmp(shell->cmds->cmd[0], "cd", 3) == 0)
		ft_cd(shell->cmds->cmd, shell->env_list);
	else if (ft_strncmp(shell->cmds->cmd[0], "pwd", 4) == 0 \
	|| ft_strncmp(shell->cmds->cmd[0], "PWD", 4) == 0)
		ft_pwd();
	else if (ft_strncmp(shell->cmds->cmd[0], "export", 7) == 0)
		ft_export(shell->cmds->cmd, shell);
	else if (ft_strncmp(shell->cmds->cmd[0], "unset", 6) == 0)
		ft_unset(shell->cmds->cmd, shell);
	else if (ft_strncmp(shell->cmds->cmd[0], "env", 4) == 0 \
	|| ft_strncmp(shell->cmds->cmd[0], "ENV", 4) == 0)
		ft_env(shell->env_list);
	else if (ft_strncmp(shell->cmds->cmd[0], "exit", 5) == 0)
		ft_exit(shell->cmds->cmd, shell);
	else
		return (1);
	return (0);
}
