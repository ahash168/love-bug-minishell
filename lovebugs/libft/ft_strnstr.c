/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahashem <ahashem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 17:03:02 by ahashem           #+#    #+#             */
/*   Updated: 2023/11/12 19:34:24 by ahashem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;

	i = 0;
	if (!*needle)
		return ((char *)haystack);
	if (!*haystack)
		return (NULL);
	while ((i + ft_strlen(needle)) <= len)
	{
		if (ft_strncmp(haystack + i, needle, ft_strlen(needle)) == 0)
		{
			return ((char *)(haystack + i));
		}
		i++;
	}
	return (0);
}
