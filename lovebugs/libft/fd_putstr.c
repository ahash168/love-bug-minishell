/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: busragordag <busragordag@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 11:30:20 by ahashem           #+#    #+#             */
/*   Updated: 2024/07/18 17:13:45 by busragordag      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	fd_putstr(int fd, char *str)
{
	int	length;
	int	i;

	if (str == NULL)
	{
		write (fd, "(null)", 6);
		return (6);
	}
	else
		length = 0;
	i = -1;
	while (str[++i] != '\0')
		length += fd_putchar(fd, str[i]);
	return (length);
}