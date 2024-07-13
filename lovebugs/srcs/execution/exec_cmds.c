/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahashem <ahashem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 10:05:53 by ahashem           #+#    #+#             */
/*   Updated: 2024/07/13 20:54:03 by ahashem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	set_redir(t_cmd *cmd)
{
	if (cmd->in != 0 && cmd->in != -1)
	{
		dup2(cmd->in, STDIN_FILENO);
		close(cmd->in);
	}
	if (cmd->out != 1 && cmd->out != -1)
	{
		dup2(cmd->out, STDOUT_FILENO);
		close(cmd->out);
	}
}

void	exec_single(t_cmd *cmd, t_env *my_env)
{
	int		std_in;
	int		std_out;

	std_in = dup(STDIN_FILENO);
	std_out = dup(STDOUT_FILENO);
	if (is_builtin(cmd->cmd[0]) == 0)
	{
		set_redir(cmd);
		exec_builtin(cmd->cmd, my_env);
		dup2(std_in, STDIN_FILENO);
		close(std_in);
		dup2(std_out, STDOUT_FILENO);
		close(std_out);
	}
}

void	exec_cmds(t_cmd *cmds, t_env *my_env)
{
	if (cmds->count == 1)
		exec_single(cmds, my_env);
	// else
	// 	exec_multiple(cmds, my_env);
}
