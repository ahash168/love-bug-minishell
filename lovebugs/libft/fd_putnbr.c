/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: busragordag <busragordag@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 11:36:41 by ahashem           #+#    #+#             */
/*   Updated: 2024/07/18 17:12:14 by busragordag      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	fd_putnbr(int fd, int nb)
{
	int		length;
	char	c;

	length = 0;
	if (nb == -2147483648)
		return (length += fd_putstr(fd, "-2147483648"));
	if (nb < 0)
	{
		length += fd_putchar (fd, '-');
		nb *= -1;
	}
	if (nb >= 10)
		length += fd_putnbr (fd, nb / 10);
	c = (nb % 10) + 48;
	length += fd_putchar(fd, c);
	return (length);
}
