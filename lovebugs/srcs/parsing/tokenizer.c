/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahashem <ahashem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 20:18:33 by ahashem           #+#    #+#             */
/*   Updated: 2024/07/25 20:29:00 by ahashem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	tokenizer(t_mini *shell)
{
	int		i;
	t_token	*current_token;
	t_token	*last_token;

	i = 0;
	last_token = NULL;
	while (shell->input[i])
	{
		current_token = ft_calloc(1, sizeof(t_token));
		if (!current_token)
			return (1);
		name_token(&(shell->input[i]), current_token);
		if (!shell->tokens)
			shell->tokens = current_token;
		else
			last_token->next = current_token;
		last_token = current_token;
		i += ft_strlen(current_token->str);
	}
	last_token->next = NULL;
	return (0);
}
