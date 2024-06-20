/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgordag <bgordag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 14:06:11 by bgordag           #+#    #+#             */
/*   Updated: 2024/06/20 14:23:55 by bgordag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_echo(char **split_input, int i, int check)
{
	while (split_input[i])
	{
		printf("%s", split_input[i]);
		if (split_input[i + 1])
			printf(" ");
		i++;
	}
	if (check)
		printf("\n");
}

int	ft_echo(char *input)
{
	int		i;
	int		check;
	char	**split_input;

	i = 1;
	check = 1;
	split_input = ft_split(input, ' ');
	while (split_input[i] && ft_strncmp(split_input[i], "-n", 2) == 0)
	{
		int j = 2;
		while (split_input[i][j] == 'n')
			j++;
		if (split_input[i][j] == '\0')
		{
			check = 0;
			i++;
		}
		else
			break;
	}
	print_echo(split_input, i, check);
	freeer(split_input);
	return (0);
}
