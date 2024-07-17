/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_single.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahashem <ahashem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 19:24:33 by ahashem           #+#    #+#             */
/*   Updated: 2024/07/16 18:42:11 by ahashem          ###   ########.fr       */
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
	return (pid);
}

void	exec_single(t_cmd *cmd, t_env *my_env, char **env)
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
	else
		cmd->pid = exec_cmd(cmd->cmd, env);
}
