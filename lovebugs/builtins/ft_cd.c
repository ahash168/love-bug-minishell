/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahashem <ahashem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 14:06:09 by bgordag           #+#    #+#             */
/*   Updated: 2024/06/21 14:55:48 by ahashem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// int	ft_cd(char **input, char **env)
// {
// 	char	*path;
// 	char	*old_pwd;
// 	char	*new_pwd;

// 	old_pwd = getcwd(NULL, 0);
// 	path = input + 3;
// 	if (!input[0] || ft_strncmp(input[0], "~", 2) == 0)
// 	{
// 		go_to_home (input, old_pwd);
// 		return ;
// 	}
// 	return (0);
// }