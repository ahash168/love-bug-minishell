/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_single.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahashem <ahashem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 19:24:33 by ahashem           #+#    #+#             */
/*   Updated: 2024/07/19 21:14:11 by ahashem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	**get_path(char **env)
{
	int		i;
	char	**paths;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
			break ;
		i++;
	}
	paths = ft_split(env[i] + 5, ':');
	i = 0;
	while (paths[i])
	{
		paths[i] = ft_strjoin(paths[i], "/", 1);
		i++;
	}
	return (paths);
}

void	path_checker(char **cmd, char **env)
{
	int		i;
	char	**paths;
	char	*command;

	paths = get_path(env);
	i = 0;
	while (paths[i])
	{
		command = ft_strjoin(paths[i], *cmd, 0);
		if (access(command, X_OK) == 0)
			*cmd = ft_strjoin(paths[i], *cmd, 1);
		free(command);
		i++;
	}
}

char	**cmd_validator(char **cmd, char **env)
{
	path_checker(&cmd[0], env);
	return (cmd);
}

int	exec_cmd(char **cmds, char **env)
{
	int		pid;
	char	**valid_cmds;

	valid_cmds = cmd_validator(cmds, env);
	pid = fork();
	if (pid == -1)
		exit(1);
	if (pid == 0)
		execve(valid_cmds[0], valid_cmds, env);
	freeer(valid_cmds);
	return (pid);
}

void	exec_single(t_mini *shell)
{
	int		std_in;
	int		std_out;

	std_in = dup(0);
	std_out = dup(1);
	// printf("%p %p\n", shell->cmds, shell->cmds->cmd);
	if (shell->cmds == NULL || shell->cmds->cmd == NULL || shell->cmds->cmd[0] == NULL)
		return ;
	if (is_builtin(shell->cmds->cmd[0]) == 0)
	{
		set_redir(shell->cmds);
		exec_builtin(shell);
		dup2(std_in, 0);
		close(std_in);
		dup2(std_out, 1);
		close(std_out);
	}
	else
		shell->cmds->pid = exec_cmd(shell->cmds->cmd, shell->env_arr);
}



// void handle_redirections_only(t_cmd *cmd)
// {
//     if (cmd->in != 0) 
// 	{
//         dup2(cmd->in, 0);
//         close(cmd->in);
//     }
//     if (cmd->out != 1) 
// 	{
//         dup2(cmd->out, 1);
//         close(cmd->out);
//     }
// }

// void execute_cmd(t_cmd *cmd)
// {
//     if (cmd->cmd == NULL || cmd->cmd[0] == NULL) {
//         // Only redirections, no command
//         handle_redirections_only(cmd);
//         return;
//     }
//     // If there is a command, execute it
//     if (fork() == 0) {
//         if (cmd->in != 0) {
//             dup2(cmd->in, 0);
//             close(cmd->in);
//         }
//         if (cmd->out != 1) {
//             dup2(cmd->out, 1);
//             close(cmd->out);
//         }
//         execvp(cmd->cmd[0], cmd->cmd);
//         perror("execvp failed");
//         exit(1);
//     } else {
//         wait(NULL);
//     }
// }

