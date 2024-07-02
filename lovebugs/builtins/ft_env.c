/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: busragordag <busragordag@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 14:06:14 by bgordag           #+#    #+#             */
/*   Updated: 2024/06/23 23:46:27 by busragordag      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_env(t_env *my_env)
{
	t_env *current;
	current = my_env;
	while (current)
	{
		printf("%s=%s\n", current->var, current->value);
		current = current->next;
	}
	return (0);
}
