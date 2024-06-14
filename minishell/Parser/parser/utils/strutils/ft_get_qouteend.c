/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_qouteend.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgordag <mgordag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 22:42:40 by mgordag           #+#    #+#             */
/*   Updated: 2022/10/17 22:42:41 by mgordag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser_utils.h"

int	ft_get_qoueteend(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			i += parser_quote_endidx(&str[i + 1], c);
		else if (str[i] == ' ')
			break ;
		else if (str[i])
			i++;
	}
	return (i);
}
