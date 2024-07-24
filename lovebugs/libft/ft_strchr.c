/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: busragordag <busragordag@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 18:59:43 by ahashem           #+#    #+#             */
/*   Updated: 2024/07/21 23:01:37 by busragordag      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	*str;
	int		i;

	i = 0;
	if (!s)
		return (0);
	str = (char *)s;
	while (str[i] != '\0')
	{
		if (str[i] == (unsigned char)c)
			return (str + i);
		i++;
	}
	if (str[i] == (unsigned char)c)
		return (str + i);
	return (0);
}
