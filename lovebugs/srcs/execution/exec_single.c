/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_single.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahashem <ahashem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 19:24:33 by ahashem           #+#    #+#             */
/*   Updated: 2024/07/23 22:19:55 by ahashem          ###   ########.fr       */
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

void	exec_single(t_mini *shell, t_cmd *cmds)
{
	char	**valid_cmds;

	valid_cmds = NULL;
	if (cmds == NULL || cmds->cmd == NULL || cmds->cmd[0] == NULL)
		return ;
	if (is_builtin(cmds->cmd[0]) == 0)
		exec_builtin(shell, cmds);
	else
	{
		valid_cmds = cmd_validator(cmds->cmd, shell->env_arr);
		execve(valid_cmds[0], valid_cmds, shell->env_arr);
		// exec_cmd(cmds->cmd, shell->env_arr);
	}	
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

