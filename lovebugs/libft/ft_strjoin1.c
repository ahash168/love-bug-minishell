/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahashem <ahashem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 14:51:16 by ahashem           #+#    #+#             */
/*   Updated: 2024/07/24 16:03:17 by ahashem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin1(char const *s1, char const *s2)
{
	size_t	size;
	char	*res;

	if (!s1 && !s2)
		return (NULL);
	size = 0;
	size = ft_strlen((char *)s1) + ft_strlen((char *)s2);
	res = (char *)malloc(sizeof(char) * (size + 1));
	if (!res)
		return (NULL);
	if (s1 && s2)
	{
		ft_strcat(ft_strcpy(res, (char *)s1), (char *)s2);
		return (res);
	}
	else if (s1 != NULL && s2 == NULL)
	{
		return (free((char *)s2), ft_strcpy(res, (char *)s1));
	}
	else if (s1 == NULL && s2 != NULL)
		return (free((char *)s1), ft_strcpy(res, (char *)s2));
	else
		return (free((char *)s1), NULL);
}
