/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgordag <mgordag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 11:21:54 by mgordag           #+#    #+#             */
/*   Updated: 2022/10/18 11:21:55 by mgordag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t num)
{
	size_t	i;

	if (dest == src || !num)
		return (dest);
	i = 0;
	while (i < num)
	{
		*((char *)dest + i) = *((char *)src + i);
		i++;
	}
	return (dest);
}
