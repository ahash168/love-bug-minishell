/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahashem <ahashem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 18:30:43 by ahashem           #+#    #+#             */
/*   Updated: 2024/06/20 11:55:18 by ahashem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**freeer(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
	return (NULL);
}

void	error_message(int n)
{
	if (n == 1)
		write(1, "Wrong format.\nExpected format: "
			"./so_long [map_name].ber", 56);
	write(1, "\n", 1);
}

void	errorer(void *ptr, int dimension, int n)
{
	if (dimension == 1)
	{
		if (ptr != NULL)
			free(ptr);
	}
	else
		free(freeer((char **)ptr));
	write(1, "--     Error.     --\n", 22);
	error_message(n);
	exit(1);
}
