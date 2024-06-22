/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahashem <ahashem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 14:06:18 by bgordag           #+#    #+#             */
/*   Updated: 2024/06/21 19:53:21 by ahashem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// int get_var(char **env, char *var)
// {
// 	int		i;

// 	i = 0;
// 	while (env[i])
// 	{
// 		if (ft_strncmp(env[i], var, ft_strlen(var)) == 0)
// 			return (1);
// 		i++;
// 	}
// 	return (0);
// }

// int	ft_strset(char *set, char strc)
// {
// 	int	i;
// 	int	x;

// 	i = 0;
// 	x = 1;
// 	while (set[i])
// 	{
// 		if (strc == set[i])
// 			x = 0;
// 		i++;
// 	}
// 	if (x == 0)
// 		return (0);
// 	else
// 		return (1);
// }

// int ft_export(char **input, char **env)
// {
// 	if (ft_strset(input[1], '='))
// 		return (0);
// 	if (get_var(env, input[1]))
// 	{
		
// 	}
// 	return (0);
// }