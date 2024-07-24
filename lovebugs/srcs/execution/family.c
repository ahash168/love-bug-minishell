/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   family.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahashem <ahashem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 19:53:57 by ahashem           #+#    #+#             */
/*   Updated: 2024/07/24 19:54:34 by ahashem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	child(t_mini *shell, t_cmd *current)
{
	set_redir(shell, current);
	if (shell->cmd_count > 1)
	{
		close(shell->pipe_fd[0]);
		if (current->out == 1)
			dup2(shell->pipe_fd[1], 1);
		close(shell->pipe_fd[1]);
	}
	shell->env_arr = list_to_array(shell->env_list);
	exec_single(shell, current);
	free_shell(shell);
	exit(1);
}

void	parent(t_mini *shell, t_cmd *current)
{
	if (shell->cmd_count > 1)
	{
		close(shell->pipe_fd[1]);
		dup2(shell->pipe_fd[0], 0);
		close(shell->pipe_fd[0]);
	}
	if (current->out != 1)
		close(current->out);
	if (current->in != 0)
		close(current->in);
}
