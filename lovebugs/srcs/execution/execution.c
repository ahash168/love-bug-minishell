/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahashem <ahashem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 10:05:53 by ahashem           #+#    #+#             */
/*   Updated: 2024/07/14 15:56:04 by ahashem          ###   ########.fr       */
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
	{
		execve(valid_cmds[0], valid_cmds, env);
	}
	return (pid);
}

void	set_redir(t_cmd *cmd)
{
	if (cmd->in != 0 && cmd->in != -1)
	{
		dup2(cmd->in, STDIN_FILENO);
		close(cmd->in);
	}
	if (cmd->out != 1 && cmd->out != -1)
	{
		dup2(cmd->out, STDOUT_FILENO);
		close(cmd->out);
	}
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
	{
		cmd->pids[0] = exec_cmd(cmd->cmd, env);
	}
}

int	execution(t_cmd *cmds, t_env *my_env)
{
	char	**env;
	int		i;
	int		status;

	env = list_to_array(my_env);
	if (cmds->count == 1)
		exec_single(cmds, my_env, env);
	// else
	// 	exec_multiple(cmds, my_env);
	i = 0;
	while (cmds->pids[i])
		waitpid(cmds->pids[i++], &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (1);
}
