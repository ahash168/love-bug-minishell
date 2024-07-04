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
	while (current && current->type != WORD)
		current = current->next;
	if (current && current->type == WORD)
		current->type = CMD;
	while (current && current->next && current->next->type != PIPE)
	{
		current = current->next;
		if (current->type == WORD)
			current->type = ARG;
	}
}

void	path_tokens(t_token *tokens)
{
	t_token	*current;
	char	*redir_str;

	current = tokens;
	while (current)
	{
		if (current->type == REDIR)
		{
			redir_str = current->str;
			if (current && current->next->type == SPACES)
				current = current->next;
			if (current)
			{
				if (ft_strncmp(redir_str, "<<", 2) == 0)
					current->next->type = DELIM;
				else
					current->next->type = PATH;
			}
		}
		current = current->next;
	}
}

int	cmd_counter(t_token *tokens)
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

void	rename_tokens(t_token *tokens)
{
	t_token	*current;
	int		cmd_count;

	current = tokens;
	cmd_count = cmd_counter(tokens);
	path_tokens(tokens);
	while (current && cmd_count-- > 0)
	{
		cmdarg_tokens(current);
		while (current && current->type != PIPE)
			current = current->next;
		if (current)
			current = current->next;
	}
}
