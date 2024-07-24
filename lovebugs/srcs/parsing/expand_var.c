/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahashem <ahashem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 14:42:07 by ahashem           #+#    #+#             */
/*   Updated: 2024/07/07 14:42:07 by ahashem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*var_expansion(char *str, t_mini *shell)
{
	char	*expanded;
	char	var_name[256];
	char	*var_value;
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	expanded = ft_calloc(1024, sizeof(char));
	while (str[i])
	{
		if (str[i] == '$')
		{
			i++;
			k = 0;
			while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
				var_name[k++] = str[i++];
			var_name[k] = '\0';
			var_value = ft_getenv(var_name, shell->env_list);
			if (var_value)
			{
				ft_strcpy(&expanded[j], var_value);
				j += ft_strlen(var_value);
			}
		}
		else
			expanded[j++] = str[i++];
	}
	expanded[j] = '\0';
	return (expanded);
}

char	*expand_with_single_quotes(char *str, t_mini *shell)
{
	char	*expanded;
	int		i;
	int		j;
	int		k;
	int		in_single_quote;
	char	var_name[256];
	char	*var_value;

	in_single_quote = 0;
	i = 0;
	j = 0;
	expanded = ft_calloc(1024, sizeof(char));
	while (str[i])
	{
		if (str[i] == '\'')
		{
			in_single_quote = !in_single_quote;
			expanded[j++] = str[i++];
		}
		else if (str[i] == '$' && !in_single_quote)
		{
			i++;
			k = 0;
			while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
				var_name[k++] = str[i++];
			var_name[k] = '\0';
			var_value = ft_getenv(var_name, shell->env_list);
			if (var_value)
			{
				ft_strcpy(&expanded[j], var_value);
				j += ft_strlen(var_value);
			}
		}
		else
			expanded[j++] = str[i++];
	}
	expanded[j] = '\0';
	return (expanded);
}

void	expand_var(t_mini *shell)
{
	t_token	*current;
	char	*new_str;

	current = shell->tokens;
	while (current)
	{
		if (current->type == DOUBLE || current->type == VAR)
		{
			new_str = var_expansion(current->str, shell);
			free(current->str);
			current->str = new_str;
		}
		else if (current->type == PATH || current->type == ARG
			|| current->type == CMD)
		{
			new_str = expand_with_single_quotes(current->str, shell);
			free(current->str);
			current->str = new_str;
		}
		current = current->next;
	}
}
