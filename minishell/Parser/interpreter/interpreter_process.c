/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter_process.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgordag <mgordag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 22:41:25 by mgordag           #+#    #+#             */
/*   Updated: 2022/10/17 22:41:26 by mgordag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_interpreter.h"

char	**interpreter_array_format(char **arr, t_vars *g_data)
{
	int		i;
	char	*tmp;

	i = 0;
	while (arr[i])
	{
		tmp = ft_check_quote(arr[i], g_data);
		if (tmp != NULL)
		{
			free(tmp);
			tmp = arr[i];
			arr[i] = ft_check_quote(arr[i], g_data);
			free(tmp);
		}
		i++;
	}
	return (arr);
}
