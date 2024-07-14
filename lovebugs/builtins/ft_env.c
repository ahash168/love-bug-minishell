/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahashem <ahashem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 14:06:14 by bgordag           #+#    #+#             */
/*   Updated: 2024/07/14 12:54:11 by ahashem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_env(t_env *my_env)
{
	t_env	*current;

	current = my_env;
	while (current)
	{
		ft_putstr_fd(current->var, 1);
		ft_putstr_fd("=", 1);
		ft_putendl_fd(current->value, 1);
		current = current->next;
	}
	return (0);
}
