/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_tokens.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahashem <ahashem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 17:30:04 by ahashem           #+#    #+#             */
/*   Updated: 2024/07/02 17:35:20 by ahashem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	join_tokens(t_token *tokens)
{
	t_token	*current;
	
	current = tokens;
	while (current)
	{
		if (current->type == DELIM)
		{
			if (current->next->type == SINGLE || current->next->type == DOUBLE)
				ft_strjoin(current->str, current->next->str, 1);
		}
		current = current->next;
	}
}