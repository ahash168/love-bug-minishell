/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_tokens.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahashem <ahashem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 17:30:04 by ahashem           #+#    #+#             */
/*   Updated: 2024/07/17 15:32:41 by ahashem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	join_tokens(t_mini *shell)
{
	t_token	*current;
	t_token	*next;

	current = shell->tokens;
	while (current)
	{
		if (current->type == SINGLE || current->type == DOUBLE
			|| current->type == VAR || current->type == WORD)
		{
			next = current->next;
			while (next && (next->type == SINGLE || next->type == DOUBLE
					|| next->type == VAR || next->type == WORD))
			{
				current->str = ft_strjoin(current->str, next->str, 1);
				current->next = next->next;
				current->type = WORD;
				free(next->str);
				next = current->next;
			}
		}
		current = current->next;
	}
}
