/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parser_mem.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgordag <mgordag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 22:43:06 by mgordag           #+#    #+#             */
/*   Updated: 2022/10/17 22:43:07 by mgordag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_utils.h"

char	*ft_free(char *ptr)
{
	if (ptr)
		free(ptr);
	return (NULL);
}

char	**ft_double_free(char **ptr, size_t size)
{
	size_t	i;

	if (ptr == NULL)
		return (NULL);
	i = 0;
	while (i < size)
	{
		if (ptr[i])
			free(ptr[i]);
		i++;
	}
	free(ptr);
	return (NULL);
}
