/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahashem <ahashem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 12:33:04 by ahashem           #+#    #+#             */
/*   Updated: 2023/11/12 19:33:42 by ahashem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t			i;
	unsigned char	*tempd;
	unsigned char	*temps;

	tempd = (unsigned char *)dst;
	temps = (unsigned char *)src;
	i = -1;
	if (!dst && !src)
		return (0);
	if (dst <= src)
	{
		while (++i < len)
			tempd[i] = temps[i];
	}
	else
	{
		while (len--)
			tempd[len] = temps[len];
	}
	return (dst);
}
