/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahashem <ahashem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 13:43:51 by ahashem           #+#    #+#             */
/*   Updated: 2024/06/22 13:45:47 by ahashem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_free(void *ptr)
{
	if (ptr == NULL)
		return (NULL);
	free(ptr);
	return (NULL);
}

void	*ft_realloc(void *ptr, size_t new_size, size_t old_size)
{
	void	*new_ptr;

	if (ptr == NULL)
		return (ft_calloc(new_size, 1));
	if (new_size == 0)
	{
		ptr = ft_free(ptr);
		return (NULL);
	}
	new_ptr = ft_calloc(new_size, 1);
	if (new_ptr == NULL)
		return (NULL);
	ft_memcpy(new_ptr, ptr, old_size);
	ptr = ft_free(ptr);
	return (new_ptr);
}