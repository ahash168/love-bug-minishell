/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_put_address.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahashem <ahashem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 16:02:28 by ahashem           #+#    #+#             */
/*   Updated: 2024/07/24 16:02:29 by ahashem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	fd_put_address(int fd, unsigned long long nb)
{
	int		length;
	int		nbr;
	char	res;

	length = 0;
	if (nb >= 16)
		length += fd_put_address (fd, nb / 16);
	nbr = nb % 16;
	if (nbr < 10)
		res = nbr + 48;
	if (nbr >= 10)
		res = nbr + 87;
	length += fd_putchar(fd, res);
	return (length);
}
