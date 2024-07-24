/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahashem <ahashem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 10:05:53 by ahashem           #+#    #+#             */
/*   Updated: 2024/07/23 22:39:00 by ahashem          ###   ########.fr       */
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

void	set_redir(t_mini *shell, t_cmd *current)
{
	(void) shell;
	if (current->in != 0)
	{
		dup2(current->in, 0);
		close(current->in);
		// printf("Closed in (%d) and duped it to stdin for cmd: %s\n", current->in, current->cmd[0]);
	}
	if (current->out != 1)
	{
		dup2(current->out, 1);
		close(current->out);
		// printf("Closed out (%d) and duped it to stdout for cmd: %s\n", current->out, current->cmd[0]);
	}
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
	// printf("cmd_count = %d\n", shell->cmd_count);
	if (shell->cmd_count == 1 && !is_builtin(shell->cmds->cmd[0]))
	{
		set_redir(shell, current);
		exec_builtin(shell, current);
	}
	else
	{
		while (current)
		{
			if (current->next)
				if (pipe(shell->pipe_fd) == -1)
					exit(0);
			current->pid = fork();
			if (current->pid == -1)
				exit(1);
			if (current->pid == 0)
			{
				set_redir(shell, current);
				close(shell->pipe_fd[0]);
				if (current->out == 1)
					dup2(shell->pipe_fd[1], 1);
				close(shell->pipe_fd[1]);
				shell->env_arr = list_to_array(shell->env_list);
				exec_single(shell, current);
				free_shell(shell);
				exit(1);
			}
			else
			{
				close(shell->pipe_fd[1]);
				dup2(shell->pipe_fd[0], 0);
				close(shell->pipe_fd[0]);
			}
			current = current->next;
		}
		current = shell->cmds;
		while (current)
		{
			if (current->pid)
				waitpid(current->pid, &status, 0);
			current = current->next;
		}
		dup2(stdin, 0);
		close(stdin);
		dup2(stdout, 1);
		close(stdout);
		if (WIFEXITED(status))
			return (WEXITSTATUS(status));
		return (1);
	}
	dup2(stdin, 0);
	close(stdin);
	dup2(stdout, 1);
	close(stdout);
	return (0);
}





// void	set_pipes(t_mini *shell, t_cmd *cmds)
// {
// 	t_cmd *current;

// 	current = cmds;
// 	while (current && current->next)
// 	{
// 		if (pipe(shell->pipe_fd) == -1)
// 		{
// 			perror("pipe");
// 			exit(1);
// 		}
// 		// printf("Opened pipe: READ[%d] WRITE[%d]\n", shell->pipe_fd[0], shell->pipe_fd[1]);
// 		if (current->out == 1)
// 			current->out = shell->pipe_fd[1];
// 		if (current->next->in == 0)
// 			current->next->in = shell->pipe_fd[0];
// 		current = current->next;
// 	}
// }


// int execution(t_mini *shell)
// {
//     t_cmd *current;
//     int status;
//     int stdin_copy;
//     int stdout_copy;

// 	current = shell->cmds;
//     stdin_copy = dup(0);
//     stdout_copy = dup(1);
//     if (shell->cmd_count == 1 && !is_builtin(shell->cmds->cmd[0])) {
//         set_redir(shell, current);
//         exec_builtin(shell, current);
//     }
// 	else
// 	{
//         set_pipes(shell, current);
//         while (current)
// 		{
//             current->pid = fork();
//             if (current->pid == -1)
// 			{
//                 perror("fork");
//                 exit(EXIT_FAILURE);
//             }
//             if (current->pid == 0)
// 			{
//                 set_redir(shell, current);
//                 shell->env_arr = list_to_array(shell->env_list);
//                 exec_single(shell, current);
//                 exit(1);
//             }
// 			else
// 			{
//                 if (current->in != 0)
// 					close(current->in);
//                 if (current->out != 1)
// 					close(current->out);
//                 if (current->next)
// 					close(shell->pipe_fd[1]);
//             }
//             current = current->next;
//         }
//         current = shell->cmds;
//         while (current) {
//             if (current->pid)
// 				waitpid(current->pid, &status, 0);
//             current = current->next;
//         }
//     }
//     dup2(stdin_copy, 0);
//     dup2(stdout_copy, 1);
//     close(stdin_copy);
//     close(stdout_copy);
// 	if (WIFEXITED(status))
// 		return WEXITSTATUS(status);
// 	else
// 		return (1);
// }







































// void	set_redir(t_mini *shell, t_cmd *current)
// {
// 	(void) shell;
// 	if (current->in != 0)
// 	{
// 		dup2(current->in, 0);
// 		close(current->in);
// 		// printf("Closed in (%d) and duped it to stdin\n", current->in);
// 	}
// 	if (current->out != 1)
// 	{
// 		dup2(current->out, 1);
// 		close(current->out);
// 		// printf("Closed out (%d) and duped it to stdput\n", current->out);
// 	}
// 	// if (shell->cmd_count > 1)
// 	// {
// 	// 	if (i < shell->cmd_count - 1 && current->out == 1)
// 	// 	{
// 	// 		dup2(shell->pipe_fd[1], 1);
// 	// 		close(shell->pipe_fd[1]);
// 	// 		// printf("We have more than one cmd left, duped write end of pipe (%d) to stdout\n", shell->pipe_fd[1]);
// 	// 	}
// 	// 	// if (i < shell->cmd_count - 1)
// 	// 	// {
// 	// 	// 	close(shell->pipe_fd[0]);
// 	// 	// 	printf("We have more than one cmd left, so closed the read end of pipe (%d)\n", shell->pipe_fd[0]);
// 	// 	// }
// 	// 	if (i != shell->cmd_count - 1 && current->out != 1)
// 	// 	{
// 	// 		close(shell->pipe_fd[1]);
// 	// 		// printf("If we already have a redirection out, we close the write end of the pipe (%d)\n", shell->pipe_fd[1]);	
// 	// 	}
// 	// }
// }

// int	execution(t_mini *shell)
// {
// 	t_cmd	*current;
// 	int		status;
// 	int		stdin;
// 	int		stdout;

// 	status = 0;
// 	stdin = dup(0);
// 	stdout = dup(1);
// 	current = shell->cmds;
// 	printf("cmd_count = %d, is builtin = %d\n", shell->cmd_count, is_builtin(shell->cmds->cmd[0]));
// 	if (shell->cmd_count == 1 && !is_builtin(shell->cmds->cmd[0]))
// 	{
// 		if (current->in != 0)
// 		{
// 			dup2(current->in, 0);
// 			close(current->in);
// 		}
// 		if (current->out != 1)
// 		{
// 			dup2(current->out, 1);
// 			close(current->out);
// 		}
// 		exec_builtin(shell, current);
// 		dup2(stdin, 0);
// 		close(stdin);
// 		dup2(stdout, 1);
// 		close(stdout);
// 	}
// 	else
// 	{
// 		set_pipes(shell, current);
// 		while (current)
// 		{
// 			current->pid = fork();
// 			if (current->pid == -1)
// 				exit(1);
// 			if (current->pid == 0)
// 			{
// 				set_redir(shell, current);
// 				exec_single(shell, current);
// 			}
// 			else
// 			{
// 				if (current->in != 0)
// 					close(current->in);
// 				if (current->out != 1)
// 					close(current->out);
// 			}
// 			current = current->next;
// 		}
// 		// while (i < shell->cmd_count)
// 		// {
// 		// 	if (i < shell->cmd_count - 1)
// 		// 	{
// 		// 		pipe(shell->pipe_fd);
// 		// 		printf("Pipe opened. Read end (%d) and write end (%d)\n", shell->pipe_fd[0], shell->pipe_fd[1]);			
// 		// 	}
// 		// 	current->pid = fork();
// 		// 	if (current->pid == 0)
// 		// 	{
// 		// 		set_redir(shell, current, i);
// 		// 		shell->env_arr = list_to_array(shell->env_list);
// 		// 		exec_single(shell, current);
// 		// 		free_shell(shell);
// 		// 		exit(0);
// 		// 	}
// 		// 	if (current->in != 0)
// 		// 	{
// 		// 		close(current->in);
// 		// 		// printf("Closing in (%d)\n", current->in);
// 		// 	}
// 		// 	if (i < shell->cmd_count - 1)
// 		// 	{
// 		// 		close(shell->pipe_fd[1]);
// 		// 		// printf("More than one cmd left, so closing write end of pipe (%d)\n", shell->pipe_fd[1]);
// 		// 	}
// 		// 	if (shell->cmd_count > 1 && current->next->in == 0)
// 		// 	{
// 		// 		// printf("More than one cmd left, so making the input of next (%d) equal to read end of pipe (%d)\n", current->next->in, shell->pipe_fd[0]);
// 		// 		current->next->in = shell->pipe_fd[0];
// 		// 	}
// 		// 	current = current->next;
// 		// 	i++;
// 		// }
		
// 		current = shell->cmds;
// 		while (current)
// 		{
// 			if (current->pid)
// 				waitpid(current->pid, &status, 0);
// 			current = current->next;
// 		}
// 		dup2(stdin, 0);
// 		close(stdin);
// 		dup2(stdout, 1);
// 		close(stdout);
// 		if (WIFEXITED(status))
// 			return (WEXITSTATUS(status));
// 		return (1);
// 	}
// 	dup2(stdin, 0);
// 	close(stdin);
// 	dup2(stdout, 1);
// 	close(stdout);
// 	return (0);
// }

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

// int	execution(t_mini *shell)
// {
// 	t_cmd	*current;
// 	int		status;
// 	int		stdin;
// 	int		stdout;
// 	status = 0;
// 	stdin = dup(0);
// 	stdout = dup(1);
// 	current = shell->cmds;
// 	printf("cmd_count = %d\n", shell->cmd_count);
// 	if (shell->cmd_count == 1 && !is_builtin(shell->cmds->cmd[0]))
// 	{
// 		set_redir(shell, current);
// 		exec_builtin(shell, current);
// 	}
// 	else
// 	{
// 		// set_pipes(shell, current);
// 		while (current)
// 		{
// 			if (current->next)
// 			{
// 				if (pipe(shell->pipe_fd) == -1)
// 					exit(0);
// 				printf("Opened pipe: READ[%d] WRITE[%d]\n", shell->pipe_fd[0], shell->pipe_fd[1]);
// 				if (current->out == 1)
// 					current->out = shell->pipe_fd[1];
// 				else
// 					close(shell->pipe_fd[1]);
// 				if (current->next->in == 0)
// 					current->next->in = shell->pipe_fd[0];
// 				else
// 					close(shell->pipe_fd[0]);
// 			}	
// 			current->pid = fork();
// 			if (current->pid == -1)
// 				exit(1);
// 			if (current->pid == 0)
// 			{
// 				set_redir(shell, current);
// 				shell->env_arr = list_to_array(shell->env_list);
// 				exec_single(shell, current);
// 			}
// 			else
// 			{
// 				if (current->in != 0)
// 					close(current->in);
// 				if (current->out != 1)
// 					close(current->out);
// 				// if (current->next && current->next->in != 0)
//                 //     close(current->next->in);
// 			}
// 			current = current->next;
// 		}
// 		current = shell->cmds;
// 		while (current)
// 		{
// 			if (current->pid)
// 				waitpid(current->pid, &status, 0);
// 			current = current->next;
// 		}
// 		dup2(stdin, 0);
// 		close(stdin);
// 		dup2(stdout, 1);
// 		close(stdout);
// 		if (WIFEXITED(status))
// 			return (WEXITSTATUS(status));
// 		return (1);
// 	}
// 	dup2(stdin, 0);
// 	close(stdin);
// 	dup2(stdout, 1);
// 	close(stdout);
// 	return (0);
// }
