/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahashem <ahashem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 16:02:22 by ahashem           #+#    #+#             */
/*   Updated: 2024/07/24 16:02:52 by ahashem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	fd_printf(int fd, const char *str, ...)
{
	int		i;
	va_list	ptr;
	int		length;

	length = 0;
	i = 0;
	va_start (ptr, str);
	while (str[i] != '\0')
	{
		if (str[i] != '%')
		{
			length += fd_putchar (fd, str[i]);
			i++;
		}
		else
		{
			length += fd_parse (fd, ptr, str[i + 1]);
			i += 2;
		}
	}
	va_end (ptr);
	return (length);
}
