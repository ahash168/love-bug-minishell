/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_put_hex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahashem <ahashem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 16:02:31 by ahashem           #+#    #+#             */
/*   Updated: 2024/07/24 16:02:32 by ahashem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	fd_put_hex(int fd, unsigned int nb, char c)
{
	int			length;
	int			d;
	long long	nbr;
	char		res;

	length = 0;
	if (c == 'x')
		d = 87;
	if (c == 'X')
		d = 55;
	if (nb >= 16)
		length += fd_put_hex (fd, nb / 16, c);
	nbr = nb % 16;
	if (nbr < 10)
		res = nbr + 48;
	if (nbr >= 10)
		res = nbr + d;
	length += fd_putchar(fd, res);
	return (length);
}
