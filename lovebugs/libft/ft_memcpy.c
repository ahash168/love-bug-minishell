/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahashem <ahashem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 11:56:24 by ahashem           #+#    #+#             */
/*   Updated: 2023/11/12 19:33:40 by ahashem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*tempd;
	unsigned char	*temps;

	tempd = (unsigned char *)dst;
	temps = (unsigned char *)src;
	i = -1;
	if (!dst && !src)
		return (0);
	while (++i < n)
		tempd[i] = temps[i];
	return (dst);
}
