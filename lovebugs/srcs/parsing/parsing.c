/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahashem <ahashem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 14:21:00 by ahashem           #+#    #+#             */
/*   Updated: 2024/07/24 20:06:16 by ahashem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	tokenizer(t_mini *shell)
{
	int		i;
	t_token	*current_token;
	t_token	*last_token;

	i = 0;
	last_token = NULL;
	while (shell->input[i])
	{
		current_token = ft_calloc(1, sizeof(t_token));
		name_token(&(shell->input[i]), current_token);
		if (!shell->tokens)
			shell->tokens = current_token;
		else
			last_token->next = current_token;
		last_token = current_token;
		i += ft_strlen(current_token->str);
	}
	last_token->next = NULL;
}

int	parsing(t_mini *shell)
{
	quote_checker(shell);
	tokenizer(shell);
	parse_tokens(shell);
	join_tokens(shell);
	rename_tokens(shell);
	expand_var(shell);
	quote_remover(shell);
	init_cmds(shell);
	init_redir(shell);
	return (0);
}
