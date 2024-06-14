/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter_init.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgordag <mgordag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 22:41:19 by mgordag           #+#    #+#             */
/*   Updated: 2022/10/17 22:41:20 by mgordag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_interpreter.h"

void	interpreter_qouete_init(const char *str, t_interpreter_quote *v)
{
	v->i = -1;
	v->env_len = 0;
	v->len = ft_strlen(str);
}

int	ft_set_envlen(int *env_len, int val)
{
	*env_len = val;
	return (val);
}
