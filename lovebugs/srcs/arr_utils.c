/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arr_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahashem <ahashem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 18:37:10 by ahashem           #+#    #+#             */
/*   Updated: 2024/06/20 11:47:24 by ahashem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	arrlen(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}

int	arrchar_count(char **arr, char c)
{
	int	i;
	int	j;
	int	x;

	i = 0;
	j = 0;
	x = 0;
	while (arr[i])
	{
		j = 0;
		while (arr[i][j])
		{
			if (arr[i][j++] == c)
				x++;
		}
		i++;
	}
	return (x);
}

char	**arrcopy(char **arr)
{
	int		i;
	char	**copy;

	i = 0;
	copy = malloc(sizeof(char *) * (arrlen(arr) + 1));
	if (!copy)
		return (NULL);
	while (arr[i])
	{
		copy[i] = malloc(sizeof(char) * (ft_strlen(arr[i]) + 1));
		ft_strlcpy(copy[i], arr[i], ft_strlen(arr[i]) + 1);
		i++;
	}
	copy[i] = NULL;
	return (copy);
}

char	*arrjoin(char **arr)
{
	int		i;
	int		j;
	int		k;
	char	*str;

	i = 0;
	k = 0;
	str = malloc(sizeof(char) * ((arrlen(arr) - 1) * (ft_strlen(arr[0]))) + 1);
	if (!str)
		return (NULL);
	while (arr[i])
	{
		j = 0;
		while (arr[i][j])
			str[k++] = arr[i][j++];
		i++;
	}
	str[k] = '\0';
	return (str);
}
