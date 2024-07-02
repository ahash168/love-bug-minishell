/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rename_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahashem <ahashem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 20:53:30 by ahashem           #+#    #+#             */
/*   Updated: 2024/06/28 20:53:30 by ahashem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	cmdarg_tokens(t_token *tokens)
{
	t_token	*current;

	current = tokens;
	while (current)
	{
		if (current->type == REDIR)
		{
			if (current->next->type == SPACES)
				current = current->next;
			if (!ft_strncmp(current->str, "<<", 2))
				current->next->type = DELIM;
			else
				current->next->type = PATH;
		}
		current = current->next;
	}
}

void	path_tokens(t_token *tokens)
{
	t_token	*current;

	current = tokens;
	while (current)
	{
		if (current->type == REDIR)
		{
			if (current->next->type == SPACES)
				current = current->next;
			if (!ft_strncmp(current->str, "<<", 2))
				current->next->type = DELIM;
			else
				current->next->type = PATH;
		}
		current = current->next;
	}
}


int cmd_counter(t_token *tokens)
{
	int		count;
	t_token	*current;

	count = 1;
	current = tokens;
	while (current)
	{
		if (current->type == PIPE)
			count++;
		current = current->next;
	}
	return (count);
}

void rename_tokens(t_token *tokens)
{
	t_token	*current;
	int		cmd_count;

	current = tokens;
	cmd_count = cmd_counter(tokens);
	printf("Number of cmds: %d\n", cmd_count);
	path_tokens(tokens);
	while (current && cmd_count-- > 0)
	{
		cmdarg_tokens(current);
		current = current->next;
	}
}