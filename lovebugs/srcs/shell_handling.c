/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahashem <ahashem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 19:49:32 by ahashem           #+#    #+#             */
/*   Updated: 2024/07/24 19:50:47 by ahashem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	init_shell(t_mini *shell)
{
	shell->input = NULL;
	shell->tokens = NULL;
	shell->cmds = NULL;
	shell->env_arr = NULL;
	shell->env_list = NULL;
	shell->cmd_count = 0;
	shell->pipe_fd[0] = 0;
	shell->pipe_fd[1] = 0;
}

void	reset_shell(t_mini *shell)
{
	if (shell->input)
	{
		free(shell->input);
		shell->input = NULL;
	}
	if (shell->tokens)
	{
		free_s_token(shell->tokens);
		shell->tokens = NULL;
	}
	if (shell->cmds)
	{
		free_s_cmd(shell->cmds);
		shell->cmds = NULL;
	}
	if (shell->env_arr)
	{
		freeer(shell->env_arr);
		shell->env_arr = NULL;
	}
	shell->cmd_count = 0;
	shell->pipe_fd[0] = 0;
	shell->pipe_fd[1] = 0;
}

void	free_shell(t_mini *shell)
{
	reset_shell(shell);
	free_s_env(shell->env_list);
	free(shell);
}
