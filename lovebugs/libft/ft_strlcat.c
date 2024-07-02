/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahashem <ahashem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 18:01:37 by ahashem           #+#    #+#             */
/*   Updated: 2023/11/12 19:34:10 by ahashem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;
	size_t	x;

	if (ft_strlen(dst) < dstsize)
		x = ft_strlen(dst) + ft_strlen(src);
	else
		x = dstsize + ft_strlen(src);
	if (dstsize == 0)
		return (ft_strlen(src));
	i = 0;
	j = ft_strlen(dst);
	while (src[i] && (j < dstsize - 1))
		dst[j++] = src[i++];
	dst[j] = '\0';
	return (x);
}
