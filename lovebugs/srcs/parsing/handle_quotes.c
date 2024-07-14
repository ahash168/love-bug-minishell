/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahashem <ahashem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 17:12:36 by ahashem           #+#    #+#             */
/*   Updated: 2024/07/07 17:12:36 by ahashem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	quote_checker(char *input)
{
	int	i;
	int	double_quote_open;
	int	single_quote_open;

	i = 0;
	double_quote_open = 0;
	single_quote_open = 0;
	while (input[i])
	{
		if (input[i] == '\"' && !single_quote_open)
			double_quote_open = !double_quote_open;
		else if (input[i] == '\'' && !double_quote_open)
			single_quote_open = !single_quote_open;
		i++;
	}
	if (double_quote_open || single_quote_open)
	{
		fprintf(stderr, "Error: Unmatched quotes detected\n");
		exit(1);
	}
}

void	quote_remover(t_token *tokens)
{
	int		i;
	int		j;
	char	*new_str;
	char	quote;
	t_token	*current;

	current = tokens;
	while (current)
	{
		if (current->type == CMD || current->type == ARG
			|| current->type == PATH || current->type == DELIM)
		{
			new_str = ft_calloc(ft_strlen(current->str) + 1, sizeof(char));
			i = 0;
			j = 0;
			quote = 0;
			while (current->str[i])
			{
				if (current->str[i] == '\'' || current->str[i] == '\"')
				{
					if (quote == 0)
						quote = current->str[i];
					else if (quote == current->str[i])
						quote = 0;
				}
				else
					new_str[j++] = current->str[i];
				i++;
			}
			new_str[j] = '\0';
			free(current->str);
			current->str = new_str;
		}
		current = current->next;
	}
}
