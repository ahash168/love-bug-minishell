/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahashem <ahashem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 09:44:11 by ahashem           #+#    #+#             */
/*   Updated: 2023/11/12 19:33:02 by ahashem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count(int n)
{
	int	units;

	if (n == -__INT_MAX__ -1)
		return (11);
	units = 1;
	if (n < 0)
	{
		units++;
		n *= -1;
	}
	while (n / 10)
	{
		units++;
		n = n / 10;
	}
	return (units);
}

char	*ft_itoa(int n)
{
	int		units;
	char	*num;

	units = count(n);
	if (n == -__INT_MAX__ -1)
		return (ft_strdup("-2147483648"));
	num = malloc(sizeof(char) * (units + 1));
	if (!num)
		return (NULL);
	num[units] = '\0';
	num[0] = 0;
	if (n < 0)
	{
		num[0] = '-';
		n *= -1;
	}
	units--;
	while (units > 0)
	{
		num[units--] = (n % 10) + '0';
		n = n / 10;
	}
	if (num[0] != '-')
		num[0] = n + '0';
	return (num);
}
