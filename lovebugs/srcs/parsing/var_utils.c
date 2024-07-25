/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahashem <ahashem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 23:55:34 by ahashem           #+#    #+#             */
/*   Updated: 2024/07/25 23:56:57 by ahashem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*extract_var_name(t_expand *exp)
{
	char	var_name[256];
	int		k;

	k = 0;
	while (exp->str[exp->i] && (ft_isalnum(exp->str[exp->i])
			|| exp->str[exp->i] == '_'))
		var_name[k++] = exp->str[exp->i++];
	var_name[k] = '\0';
	return (ft_strdup(var_name));
}

void	append_var_value(t_expand *exp, const char *var_value)
{
	ft_strcpy(&exp->expanded[exp->j], (char *)var_value);
	exp->j += ft_strlen(var_value);
}

void	get_env_var(t_expand *exp, t_mini *shell)
{
	char		*var_name;
	char		*var_value;

	var_name = extract_var_name(exp);
	var_value = ft_getenv(var_name, shell->env_list);
	free(var_name);
	if (var_value)
		append_var_value(exp, var_value);
}

void	init_expansion(t_expand *exp, char *str, t_mini *shell)
{
	exp->expanded = ft_calloc(1024, sizeof(char));
	exp->str = str;
	exp->i = 0;
	exp->j = 0;
	exp->shell = shell;
}
