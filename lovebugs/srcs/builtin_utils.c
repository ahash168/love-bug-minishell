/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahashem <ahashem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 15:11:57 by ahashem           #+#    #+#             */
/*   Updated: 2024/06/21 15:12:32 by ahashem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	line_count(char *map_str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (!map_str)
		exit(1);
	while (map_str[i++])
	{
		if (map_str[i] == '\n')
			j++;
	}
	return (j + 1);
}

int	ft_strset(char strc, char *set)
{
	int	i;
	int	x;

	i = 0;
	x = 1;
	while (set[i])
	{
		if (strc == set[i])
			x = 0;
		i++;
	}
	if (x == 0)
		return (0);
	else
		return (1);
}

int	strchar_count(char *str, char c)
{
	int	i;
	int	x;

	i = 0;
	x = 0;
	while (str[i])
	{
		if (str[i] == c)
			x++;
		i++;
	}
	return (x);
}
