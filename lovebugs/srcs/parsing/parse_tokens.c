/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahashem <ahashem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 14:19:57 by ahashem           #+#    #+#             */
/*   Updated: 2024/06/28 14:19:57 by ahashem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	parse_redir(t_token *current)
{
	current = current->next;
	if (!current)
	{
		fd_printf(2, "minishell: syntax error near"
			" unexpected token `newline'\n");
		return (1);
	}
	if (current->type == SPACES)
		current = current->next;
	if (!current || current->type == REDIR || current->type == PIPE)
	{
		fd_printf(2, "minishell: syntax error near"
			" unexpected token `newline'\n");
		return (1);
	}
	return (0);
}

int	parse_pipe(t_token *current)
{
	current = current->next;
	if (!current)
	{
		fd_printf(2, "minishell: syntax error near"
			" unexpected token `newline'\n");
		return (1);
	}
	if (current->type == SPACES)
		current = current->next;
	if (!current || current->type == PIPE)
	{
		fd_printf(2, "minishell: syntax error near"
			" unexpected token `newline'\n");
		return (1);
	}
	return (0);
}

int	parse_tokens(t_mini *shell)
{
	t_token	*current;

	current = shell->tokens;
	while (current)
	{
		if (current->type == PIPE)
		{
			if (parse_pipe(current))
				return (1);
		}
		else if (current->type == REDIR)
		{
			if (parse_redir(current))
				return (1);
		}
		current = current->next;
	}
	return (0);
}
