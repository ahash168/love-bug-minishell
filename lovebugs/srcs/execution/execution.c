/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahashem <ahashem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 10:05:53 by ahashem           #+#    #+#             */
/*   Updated: 2024/07/24 22:58:33 by ahashem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	**fill_arr(t_env *my_env, int count)
{
	int		i;
	t_env	*current;
	char	**arr;

	i = 0;
	current = my_env;
	arr = NULL;
	arr = malloc(sizeof(char *) * (count + 1));
	while (current)
	{
		arr[i] = malloc(sizeof(char) * (ft_strlen(current->var)
					+ ft_strlen(current->value) + 2));
		ft_strlcpy(arr[i], current->var, ft_strlen(current->var) + 1);
		arr[i] = ft_strjoin(arr[i], "=", 1);
		arr[i] = ft_strjoin(arr[i], current->value, 1);
		i++;
		current = current->next;
	}
	arr[i] = NULL;
	return (arr);
}

char	**list_to_array(t_env *my_env)
{
	int		count;
	char	**arr;
	t_env	*current;

	count = 0;
	current = my_env;
	while (current)
	{
		count++;
		current = current->next;
	}
	arr = fill_arr(my_env, count);
	return (arr);
}

void	set_redir(t_mini *shell, t_cmd *current)
{
	(void) shell;
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
		set_redir(shell, current);
		exec_builtin(shell, current);
	}
	else
		status = pipe_handling(shell, current);
	dup2(stdin, 0);
	dup2(stdout, 1);
	close(stdin);
	close(stdout);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else
		return (1);
}
