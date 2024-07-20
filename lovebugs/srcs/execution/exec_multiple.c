/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_multiple.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahashem <ahashem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 23:43:18 by ahashem           #+#    #+#             */
/*   Updated: 2024/07/17 23:43:18 by ahashem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	handle_pipes(t_cmd *cmds)
{
	t_cmd *current = cmds;
	while (current->next)
	{
		int pipe_fd[2];
		pipe(pipe_fd);
		current->out = pipe_fd[1];
		if (current->next->in == 0)
			current->next->in = pipe_fd[0];
		current = current->next;
	}
}

void	exec_cmds(t_cmd *cmd, t_env *my_env, char **env, t_mini *shell)
{
	(void) my_env;
	if (is_builtin(cmd->cmd[0]) == 0)
	{
		exec_builtin(shell);
		exit(0); // Ensure the child process exits after executing a builtin
	}
	else
	{
		char **valid_cmds = cmd_validator(cmd->cmd, env);
		execve(valid_cmds[0], valid_cmds, env);
		perror("execve failed"); // If execve fails, print an error
		exit(1); // Ensure the child process exits with an error code
	}
}

void	exec_multiple(t_cmd *cmds, t_env *my_env, char **env, t_mini *shell)
{
	int		status;
	t_cmd	*current_cmd = cmds;
	int		std_in = dup(0);
	int		std_out = dup(1);

	handle_pipes(cmds);

	while (current_cmd)
	{
		current_cmd->pid = fork();
		if (current_cmd->pid == -1)
		{
			perror("fork failed");
			exit(1);
		}
		if (current_cmd->pid == 0)
		{
			if (current_cmd->in != 0)
			{
				dup2(current_cmd->in, 0);
				close(current_cmd->in);
			}
			if (current_cmd->out != 1)
			{
				dup2(current_cmd->out, 1);
				close(current_cmd->out);
			}
			exec_cmds(current_cmd, my_env, env, shell);
		}
		else
		{
			if (current_cmd->in != 0)
				close(current_cmd->in);
			if (current_cmd->out != 1)
				close(current_cmd->out);
		}
		current_cmd = current_cmd->next;
	}

	current_cmd = cmds;
	while (current_cmd)
	{
		waitpid(current_cmd->pid, &status, 0);
		current_cmd = current_cmd->next;
	}

	dup2(std_in, 0);
	close(std_in);
	dup2(std_out, 1);
	close(std_out);
}