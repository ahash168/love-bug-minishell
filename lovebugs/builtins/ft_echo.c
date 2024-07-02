/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahashem <ahashem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 14:06:11 by bgordag           #+#    #+#             */
/*   Updated: 2024/06/21 13:40:05 by ahashem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_echo(char **input, int i, int check)
{
	while (input[i])
	{
		printf("%s", input[i]);
		if (input[i + 1])
			printf(" ");
		i++;
	}
	if (check)
		printf("\n");
}

int	ft_echo(char **input)
{
	int		i;
	int		check;

	i = 1;
	check = 1;
	while (input[i] && ft_strncmp(input[i], "-n", 2) == 0)
	{
		int j = 2;
		while (input[i][j] == 'n')
			j++;
		if (input[i][j] == '\0')
		{
			check = 0;
			i++;
		}
		else
			break;
	}
	print_echo(input, i, check);
	freeer(input);
	return (0);
}
