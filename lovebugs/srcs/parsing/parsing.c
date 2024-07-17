/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahashem <ahashem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 14:21:00 by ahashem           #+#    #+#             */
/*   Updated: 2024/07/17 19:14:37 by ahashem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	print_tokens(t_token *head)
{
	t_token	*current = head;
	char	*type = NULL;

	while (current != NULL)
	{
		if (current->type == SPACES)
			type = ft_strdup("[SPACES]  ");
		if (current->type == WORD)
			type = ft_strdup("[WORD]    ");
		if (current->type == CMD)
			type = ft_strdup("[CMD]     ");
		if (current->type == PATH)
			type = ft_strdup("[PATH]    ");
		if (current->type == ARG)
			type = ft_strdup("[ARG]     ");
		if (current->type == PIPE)
			type = ft_strdup("[PIPE]    ");
		if (current->type == REDIR)
			type = ft_strdup("[REDIR]   ");
		if (current->type == SINGLE)
			type = ft_strdup("[SINGLE]  ");
		if (current->type == DOUBLE)
			type = ft_strdup("[DOUBLE]  ");
		if (current->type == VAR)
			type = ft_strdup("[VAR]     ");
		if (current->type == DELIM)
			type = ft_strdup("[DELIM]   ");
		printf("Type: %s   String: %s\n", type, current->str);
		current = current->next;
	}
}

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
				type = WORD;
			if (input[i] != '?')
				while (input[i] && (ft_isalnum(input[i]) || input[i] == '_'))
					i++;
			else
				i = 2;
		}
	}
	if (type == REDIR && find_token(input[i]) == type)
		i++;
	token->type = type;
	token->str = ft_substr(input, 0, i);
}

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

// t_cmd	*parsing(char *input)
// {
// 	t_token	*tokens;
// 	t_cmd	*cmds;

// 	tokens = NULL;
// 	cmds = NULL;
// 	quote_checker(input);
// 	tokens = tokenizer(input);
// 	// printf("\nfirst\n");
// 	// print_tokens(tokens);

// 	parse_tokens(tokens);
// 	// printf("\nsecond\n");
// 	// print_tokens(tokens);

// 	join_tokens(tokens);
// 	// printf("\nthird\n");
// 	// print_tokens(tokens);

// 	rename_tokens(tokens);
// 	// printf("\nfourth\n");
// 	// print_tokens(tokens);

// 	expand_var(tokens);
// 	// printf("\nfifth\n");
// 	// print_tokens(tokens);

// 	quote_remover(tokens);
// 	// printf("\nsixth\n");
// 	// print_tokens(tokens);

// 	cmds = init_cmds(tokens);
// 	// printf("\nfirst\n");
// 	// print_cmds(cmds);

// 	init_redir(cmds, tokens);
// 	// printf("\nsecond\n");
// 	// print_cmds(cmds);

// 	return (cmds);
// }
