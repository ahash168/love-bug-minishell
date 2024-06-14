/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clearquotes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgordag <mgordag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 22:42:12 by mgordag           #+#    #+#             */
/*   Updated: 2022/10/17 22:42:13 by mgordag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser_utils.h"

char	*ft_str_clearquotes(const char *str, char *ptr)
{
	int		i;
	int		n;
	char	c;

	i = 0;
	n = 0;
	while (str[i])
	{
		if (str[i] == '"' || str[i] == '\'')
		{
			c = str[i];
			while (str[++i] && str[i] != c)
				ptr[n++] = str[i];
		}
		else
			ptr[n++] = str[i++];
	}
	return (ptr);
}
