/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_params.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgordag <mgordag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 22:44:29 by mgordag           #+#    #+#             */
/*   Updated: 2022/10/17 22:44:30 by mgordag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_builtins.h"

int	ft_sort_params(char ***argv)
{
	int		i;
	int		f;
	char	*tmp;

	if (count_line(*argv) < 2)
		return (0);
	while (1)
	{
		i = 1;
		f = 1;
		while (argv[0][i] != 0)
		{
			if (ft_strncmp(argv[0][i - 1], argv[0][i], 100) > 0)
			{
				tmp = argv[0][i - 1];
				argv[0][i - 1] = argv[0][i];
				argv[0][i] = tmp;
				f = 0;
			}
			i++;
		}
		if (f)
			return (0);
	}
	return (0);
}
