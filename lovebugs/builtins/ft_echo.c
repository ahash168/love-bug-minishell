/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahashem <ahashem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 14:06:11 by bgordag           #+#    #+#             */
/*   Updated: 2024/07/13 20:50:26 by ahashem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_echo(char **input, int i, int check)
{
	while (input[i])
	{
		ft_putstr_fd(input[i], 1);
		if (input[i + 1])
			ft_putstr_fd(" ", 1);
		i++;
	}
	if (check)
		ft_putstr_fd("\n", 1);
}

int	ft_echo(char **input)
{
	int		i;
	int		j;
	int		check;

	i = 1;
	check = 1;
	while (input[i] && ft_strncmp(input[i], "-n", 2) == 0)
	{
		j = 2;
		while (input[i][j] == 'n')
			j++;
		if (input[i][j] == '\0')
		{
			check = 0;
			i++;
		}
		else
			break ;
	}
	print_echo(input, i, check);
	// freeer(input);
	return (0);
}
