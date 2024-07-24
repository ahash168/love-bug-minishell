/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freeing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahashem <ahashem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 19:50:31 by ahashem           #+#    #+#             */
/*   Updated: 2024/07/24 19:53:01 by ahashem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_s_cmd(t_cmd *cmds)
{
	t_cmd	*current;
	t_cmd	*tmp;

	current = cmds;
	tmp = NULL;
	while (current)
	{
		tmp = current->next;
		if (current->cmd)
			freeer(current->cmd);
		free(current);
		current = tmp;
	}
}

void	free_s_token(t_token *tokens)
{
	t_token	*current;
	t_token	*tmp;

	current = tokens;
	tmp = NULL;
	while (current)
	{
		tmp = current->next;
		if (current->str)
			free(current->str);
		free(current);
		current = tmp;
	}
}

void	free_s_env(t_env *env)
{
	t_env	*current;
	t_env	*tmp;

	current = env;
	tmp = NULL;
	while (current)
	{
		tmp = current->next;
		if (current->var)
			free(current->var);
		if (current->value)
			free(current->value);
		free(current);
		current = tmp;
	}
}
