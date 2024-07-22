/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahashem <ahashem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 10:05:53 by ahashem           #+#    #+#             */
/*   Updated: 2024/07/22 17:16:11 by ahashem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	**list_to_array(t_env *my_env)
{
	int		i;
	int		count;
	char	**arr;
	t_env	*current;

	i = 0;
	count = 0;
	current = my_env;
	while (current)
	{
		count++;
		current = current->next;
	}
	arr = malloc(sizeof(char *) * (count + 1));
	current = my_env;
	while (current)
	{
		arr[i] = malloc(sizeof(char) * (ft_strlen(current->var) + ft_strlen(current->value) + 2));
		ft_strlcpy(arr[i], current->var, ft_strlen(current->var) + 1);
		arr[i] = ft_strjoin(arr[i], "=", 1);
		arr[i] = ft_strjoin(arr[i], current->value, 1);
		i++;
		current = current->next;
	}
	arr[i] = NULL;
	return (arr);
}

void	set_redir(t_mini *shell, t_cmd *current, int i)
{
	if (current->in != 0)
	{
		dup2(current->in, 0);
		close(current->in);
		printf("Closed in (%d) and duped it to stdin\n", current->in);
	}
	if (current->out != 1)
	{
		dup2(current->out, 1);
		close(current->out);
		printf("Closed out (%d) and duped it to stdput\n", current->out);
	}
	if (shell->cmd_count > 1)
	{
		if (i < shell->cmd_count - 1 && current->out == 1)
		{
			dup2(shell->pipe_fd[1], 1);
			close(shell->pipe_fd[1]);
			printf("We have more than one cmd left, duped write end of pipe (%d) to stdout\n", shell->pipe_fd[1]);
		}
		// if (i < shell->cmd_count - 1)
		// {
		// 	close(shell->pipe_fd[0]);
		// 	printf("We have more than one cmd left, so closed the read end of pipe (%d)\n", shell->pipe_fd[0]);
		// }
		if (i != shell->cmd_count - 1 && current->out != 1)
		{
			close(shell->pipe_fd[1]);
			printf("If we already have a redirection out, we close the write end of the pipe (%d)\n", shell->pipe_fd[1]);	
		}
	}
	
}

int	execution(t_mini *shell)
{
	int		i;
	t_cmd	*current;
	int		status;
	int		stdin;
	int		stdout;

	i = 0;
	status = 0;
	current = shell->cmds;
	if (shell->cmd_count == 1 && !is_builtin(shell->cmds->cmd[0]))
	{
		if (current->in != 0)
		{
			stdin = dup(0);
			dup2(current->in, 0);
			close(current->in);
		}
		if (current->out != 1)
		{
			stdout = dup(1);
			dup2(current->out, 1);
			close(current->out);
		}
		exec_builtin(shell);
		dup2(stdin, 0);
		close(stdin);
		dup2(stdout, 1);
		close(stdout);
	}
	else
	{
		while (i < shell->cmd_count)
		{
			if (i < shell->cmd_count - 1)
				pipe(shell->pipe_fd);
			current->pid = fork();
			if (current->pid == 0)
			{
				set_redir(shell, current, i);
				shell->env_arr = list_to_array(shell->env_list);
				exec_single(shell);
				free_shell(shell);
				exit(0);
			}
			if (current->in != 0)
			{
				close(current->in);
				printf("Closing in (%d)\n", current->in);
			}
			if (i < shell->cmd_count - 1)
			{
				close(shell->pipe_fd[1]);
				printf("More than one cmd left, so closing write end of pipe (%d)\n", shell->pipe_fd[1]);
			}
			if (shell->cmd_count > 1 && current->next->in == 0)
			{
				printf("More than one cmd left, so making the input of next (%d) equal to read end of pipe (%d)\n", current->next->in, shell->pipe_fd[0]);
				current->next->in = shell->pipe_fd[0];
			}
			current = current->next;
			i++;
		}
		current = shell->cmds;
		while (current)
		{
			if (current->pid)
				waitpid(current->pid, &status, 0);
			current = current->next;
		}
		if (WIFEXITED(status))
			return (WEXITSTATUS(status));
		return (1);
	}
	return (0);
}



// int	execution(t_mini *shell)
// {
// 	int		status;

// 	shell->env_arr = list_to_array(shell->env_list);
// 	if (shell->cmd_count == 1)
// 		exec_single(shell);
// 	else
// 		exec_multiple(shell->cmds, shell->env_list, shell->env_arr, shell);
// 	while (shell->cmds)
// 	{
// 		if (shell->cmds->pid)
// 			waitpid(shell->cmds->pid, &status, 0);
// 		shell->cmds = shell->cmds->next;
// 	}
// 	if (WIFEXITED(status))
// 		return (WEXITSTATUS(status));
// 	return (1);
// }
