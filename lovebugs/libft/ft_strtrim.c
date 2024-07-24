/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahashem <ahashem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 16:32:30 by ahashem           #+#    #+#             */
/*   Updated: 2024/07/24 19:16:25 by ahashem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	compare(char c, char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (c == str[i])
			return (1);
		i++;
	}
	return (0);
}

int	x_value(char const *s1, char const *set)
{
	int		i;
	int		x;

	i = 0;
	x = 0;
	while (s1[i] && compare(s1[i], (char *)set) == 1)
		i++;
	while (s1[i])
	{
		x++;
		i++;
	}
	while (s1[--i] && compare(s1[i], (char *)set) == 1)
		x--;
	return (x);
}

char	*ft_strtrim(char const *s1, char const *set, int f)
{
	int		i;
	int		j;
	int		x;
	char	*str;

	i = 0;
	j = 0;
	x = x_value(s1, set);
	str = malloc(sizeof(char) * (x + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (s1[i] && compare(s1[i], (char *)set) == 1)
		i++;
	while (x-- > 0)
		str[j++] = s1[i++];
	str[j] = '\0';
	if (f == 1)
		free((void *) s1);
	return (str);
}
