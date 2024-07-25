/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_single.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahashem <ahashem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 19:24:33 by ahashem           #+#    #+#             */
/*   Updated: 2024/07/26 00:24:30 by ahashem          ###   ########.fr       */
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
	if (env[i] == NULL)
	{
		fd_printf(2, "command not found\n");
		exit(2);
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

int	path_checker(char **cmd, char **env)
{
	int		i;
	char	**paths;
	char	*command;
	int		found;

	paths = get_path(env);
	i = 0;
	found = 1;
	while (paths[i])
	{
		command = ft_strjoin(paths[i], *cmd, 0);
		if (access(command, X_OK) == 0)
		{
			*cmd = ft_strjoin(paths[i], *cmd, 1);
			found = 0;
		}
		free(command);
		i++;
	}
	if (access(*cmd, X_OK) == 0)
		found = 0;
	return (found);
}

char	**cmd_validator(char **cmd, char **env)
{
	if (path_checker(&cmd[0], env) == 1)
		return (NULL);
	return (cmd);
}

void	exec_single(t_mini *shell, t_cmd *cmds)
{
	char	**valid_cmds;
	char	*str;

	valid_cmds = NULL;
	if (cmds == NULL || cmds->cmd == NULL || cmds->cmd[0] == NULL)
		return ;
	if (is_builtin(cmds->cmd[0]) == 0)
		exec_builtin(shell, cmds);
	else
	{
		str = ft_strdup(cmds->cmd[0]);
		valid_cmds = cmd_validator(cmds->cmd, shell->env_arr);
		if (valid_cmds == NULL)
		{
			fd_printf(2, "minishell: %s: command not found\n", str);
			free(str);
			return ;
		}
		free(str);
		execve(valid_cmds[0], valid_cmds, shell->env_arr);
	}
}
