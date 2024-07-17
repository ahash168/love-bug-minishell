/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahashem <ahashem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 10:05:53 by ahashem           #+#    #+#             */
/*   Updated: 2024/07/17 22:15:54 by ahashem          ###   ########.fr       */
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

int	execution(t_mini *shell)
{
	int		status;

	shell->env_arr = list_to_array(shell->env_list);
	if (shell->cmd_count == 1)
		exec_single(shell->cmds, shell->env_list, shell->env_arr);
	// else
	// 	exec_multiple(shell->cmds, shell->env_list, env_arr);
	while (shell->cmds)
	{
		waitpid(shell->cmds->pid, &status, 0);
		shell->cmds = shell->cmds->next;
	}
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (1);
}
