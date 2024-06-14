/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgordag <mgordag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 11:23:24 by mgordag           #+#    #+#             */
/*   Updated: 2022/10/18 11:23:25 by mgordag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str1, const char *to_find, size_t n)
{
	size_t		position;

	if (*to_find == '\0')
		return ((char *)str1);
	position = ft_strlen((char *)to_find);
	while (*str1 != '\0' && n-- >= position)
	{
		if (*str1 == *to_find && ft_memcmp(str1, to_find, position) == 0)
			return ((char *)str1);
		str1++;
	}
	return (NULL);
}
