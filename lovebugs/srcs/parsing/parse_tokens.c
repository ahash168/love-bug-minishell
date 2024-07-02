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

void parse_tokens(t_token *tokens)
{
	t_token	*current;

	current = tokens;
	while (current)
	{
		if (current->type == PIPE)
		{
			current = current->next;
			if (!current) {
				printf("error: no next after pipe\n");
				exit(1);
			}
			if (current->type == SPACES)
				current = current->next;
			if (!current || current->type == PIPE) {
				printf("error: wrong after space after pipe\n");
				exit(1);
			}
			// printf("correct\n");
		}
		else if (current->type == REDIR)
		{
			current = current->next;
			if (!current) {
				printf("error: no next after redirection\n");
				exit(1);
			}
			if (current->type == SPACES)
				current = current->next;
			if (!current || current->type == REDIR || current->type == PIPE) {
				printf("error: wrong after space after redirection\n");
				exit(1);
			}
			// printf("correct\n");
		}
		current = current->next;
	}
}