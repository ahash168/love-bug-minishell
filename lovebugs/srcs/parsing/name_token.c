/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   name_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahashem <ahashem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 19:57:38 by ahashem           #+#    #+#             */
/*   Updated: 2024/07/24 20:42:01 by ahashem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

enum e_type	find_token(char input_char)
{
	if (input_char == ' ' || input_char == '\t')
		return (SPACES);
	if (input_char == '|')
		return (PIPE);
	if (input_char == '>' || input_char == '<')
		return (REDIR);
	if (input_char == '\'')
		return (SINGLE);
	if (input_char == '\"')
		return (DOUBLE);
	if (input_char == '$')
		return (VAR);
	return (WORD);
}

int	var_type(char *input, int i, enum e_type *type)
{
	if (ft_isdigit(input[i]))
		i++;
	else if (ft_isalpha(input[i]) || input[i] == '_')
		while (input[i] && (ft_isalnum(input[i]) || input[i] == '_'))
			i++;
	else
	{
		if (!ft_isalpha(input[i]) && input[i] != '\'' && input[i] != '\"' \
		&& input[i] != '_' && input[i] != '?')
			*type = WORD;
		if (input[i] != '?')
			while (input[i] && (ft_isalnum(input[i]) || input[i] == '_'))
				i++;
		else
			i = 2;
	}
	return (i);
}

void	name_token(char *input, t_token *token)
{
	int			i;
	enum e_type	type;

	i = 0;
	type = find_token(input[i++]);
	if (type == WORD || type == SPACES)
		while (input[i] && find_token(input[i]) == type)
			i++;
	else if (type == SINGLE || type == DOUBLE)
	{
		while (input[i] && find_token(input[i]) != type)
			i++;
		if (find_token(input[i++]) != type)
			exit(1);
	}
	if (type == VAR)
		i = var_type(input, i, &type);
	if (type == REDIR && find_token(input[i]) == type)
		i++;
	token->type = type;
	token->str = ft_substr(input, 0, i);
}
