/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahashem <ahashem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 14:21:00 by ahashem           #+#    #+#             */
/*   Updated: 2024/07/04 18:18:38 by ahashem          ###   ########.fr       */
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

t_token	*tokenizer(char *input)
{
	int		i;
	t_token	*tokens_list;
	t_token	*current_token;
	t_token	*last_token;

	i = 0;
	tokens_list = NULL;
	last_token = NULL;
	while (input[i])
	{
		current_token = ft_calloc(1, sizeof(t_token));
		name_token(&input[i], current_token);
		if (!tokens_list)
			tokens_list = current_token;
		else
			last_token->next = current_token;
		last_token = current_token;
		i += ft_strlen(current_token->str);
	}
	last_token->next = NULL;
	return (tokens_list);
}

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
	t_token	*current;

	current = tokens;
	while (current)
	{
		if (current->type == SINGLE || current->type == DOUBLE)
		{
			new_str = ft_calloc(ft_strlen(current->str) - 2, sizeof(char));
			i = 0;
			j = 0;
			while (current->str[i])
			{
				if ((current->str[i] != '\'' && current->type == SINGLE)
					|| (current->str[i] != '\"' && current->type == DOUBLE))
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

// int	parsing(char *input)
// {
// 	t_token	*tokens;

// 	tokens = NULL;
// 	quote_checker(input);
// 	tokens = tokenizer(input);
// 	printf("\nfirst\n");
// 	print_tokens(tokens);
// 	parse_tokens(tokens);
// 	quote_remover(tokens);
// 	printf("\nsecond\n");
// 	print_tokens(tokens);
// 	rename_tokens(tokens);
// 	printf("\nthird\n");
// 	print_tokens(tokens);
// 	// join_tokens(tokens);
// 	// printf("\nfourth\n");
// 	// print_tokens(tokens);
// 	return (0);
// }

int	parsing(char *input)
{
	t_token	*tokens;

	tokens = NULL;
	quote_checker(input);
	tokens = tokenizer(input);
	// printf("\nfirst\n");
	// print_tokens(tokens);
	parse_tokens(tokens);
	quote_remover(tokens);
	// printf("\nsecond\n");
	// print_tokens(tokens);
	rename_tokens(tokens);
	// printf("\nthird\n");
	// print_tokens(tokens);
	init_cmds(tokens);
	return (0);
}

// t_parsed_commands parse(char *line)
// {
// 	t_parsed_commands parsed_commands;

// 	parsed_commands.commands = ft_calloc(1, sizeof(char **));
// 	parsed_commands.commands[0] = ft_split(line, ' ');
// 	parsed_commands.commands_length = 1;
// 	return parsed_commands;
// }
