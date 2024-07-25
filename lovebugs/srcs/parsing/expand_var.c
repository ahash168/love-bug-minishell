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

void	exit_code_var(t_expand *exp, t_mini *shell)
{
	exp->i++;
	if (exp->str[exp->i] == '?')
	{
		append_var_value(exp, ft_itoa(shell->exit_status));
		exp->i++;
	}
	else
		get_env_var(exp, shell);
}

char	*var_expansion(char *str, t_mini *shell)
{
	t_expand	exp;

	init_expansion(&exp, str, shell);
	while (exp.str[exp.i])
	{
		if (exp.str[exp.i] == '$')
			exit_code_var(&exp, shell);
		else
			exp.expanded[exp.j++] = exp.str[exp.i++];
	}
	exp.expanded[exp.j] = '\0';
	return (exp.expanded);
}

char	*expand_with_single_quotes(char *str, t_mini *shell)
{
	t_expand	exp;
	int			in_single_quote;

	init_expansion(&exp, str, shell);
	in_single_quote = 0;
	while (exp.str[exp.i])
	{
		if (exp.str[exp.i] == '\'')
		{
			in_single_quote = !in_single_quote;
			exp.expanded[exp.j++] = exp.str[exp.i++];
		}
		else if (exp.str[exp.i] == '$' && !in_single_quote)
			exit_code_var(&exp, shell);
		else
			exp.expanded[exp.j++] = exp.str[exp.i++];
	}
	exp.expanded[exp.j] = '\0';
	return (exp.expanded);
}

void	expand_var(t_mini *shell)
{
	t_token	*current;
	char	*new_str;

	current = shell->tokens;
	while (current)
	{
		if (current->type == DOUBLE || current->type == VAR)
			new_str = var_expansion(current->str, shell);
		else if (current->type == PATH || current->type == ARG
			|| current->type == CMD)
			new_str = expand_with_single_quotes(current->str, shell);
		else
			new_str = ft_strdup(current->str);
		free(current->str);
		current->str = new_str;
		current = current->next;
	}
}
