/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahashem <ahashem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 10:05:53 by ahashem           #+#    #+#             */
/*   Updated: 2024/07/25 23:08:18 by ahashem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	set_redir(t_mini *shell, t_cmd *current)
{
	if (current->in == -1 || current->out == -1)
	{
		fd_printf(2, "minishell: no such file or directory\n");
		shell->exit_status = 1;
		return (1);
	}
	if (current->in != 0)
	{
		dup2(current->in, 0);
		close(current->in);
	}
	if (current->out != 1)
	{
		dup2(current->out, 1);
		close(current->out);
	}
	return (0);
}

int	pipe_handling(t_mini *shell, t_cmd *current)
{
	int		status;

	while (current)
	{
		if (current->next)
			if (pipe(shell->pipe_fd) == -1)
				exit(0);
		current->pid = fork();
		if (current->pid == -1)
			exit(1);
		if (current->pid == 0)
			child(shell, current);
		else
			parent(shell, current);
		current = current->next;
	}
	current = shell->cmds;
	while (current)
	{
		if (current->pid)
			waitpid(current->pid, &status, 0);
		current = current->next;
	}
	return (status);
}

void	std_terminal(int stdin, int stdout)
{
	dup2(stdin, 0);
	dup2(stdout, 1);
	close(stdin);
	close(stdout);
}

int	execution(t_mini *shell)
{
	t_cmd	*current;
	int		status;
	int		stdin;
	int		stdout;

	status = 0;
	stdin = dup(0);
	stdout = dup(1);
	current = shell->cmds;
	if (shell->cmd_count == 1 && !is_builtin(shell->cmds->cmd[0]))
	{
		if (set_redir(shell, current))
			return (shell->exit_status);
		exec_builtin(shell, current);
	}
	else
		status = pipe_handling(shell, current);
	std_terminal(stdin, stdout);
	if (WIFEXITED(status))
		shell->exit_status = WEXITSTATUS(status);
	else
		shell->exit_status = 1;
	return (shell->exit_status);
}
