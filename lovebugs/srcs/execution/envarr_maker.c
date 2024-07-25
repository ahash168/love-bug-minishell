/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envarr_maker.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahashem <ahashem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 20:53:59 by ahashem           #+#    #+#             */
/*   Updated: 2024/07/25 20:58:32 by ahashem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	**fill_arr(t_env *my_env, int count)
{
	int		i;
	t_env	*current;
	char	**arr;

	i = 0;
	current = my_env;
	arr = NULL;
	arr = malloc(sizeof(char *) * (count + 1));
	while (current)
	{
		arr[i] = malloc(sizeof(char) * (ft_strlen(current->var)
					+ ft_strlen(current->value) + 2));
		ft_strlcpy(arr[i], current->var, ft_strlen(current->var) + 1);
		arr[i] = ft_strjoin(arr[i], "=", 1);
		arr[i] = ft_strjoin(arr[i], current->value, 1);
		i++;
		current = current->next;
	}
	arr[i] = NULL;
	return (arr);
}

char	**list_to_array(t_env *my_env)
{
	int		count;
	char	**arr;
	t_env	*current;

	count = 0;
	current = my_env;
	while (current)
	{
		count++;
		current = current->next;
	}
	arr = fill_arr(my_env, count);
	return (arr);
}
