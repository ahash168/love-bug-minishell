/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgordag <mgordag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 22:44:16 by mgordag           #+#    #+#             */
/*   Updated: 2022/10/17 22:44:17 by mgordag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_builtins.h"

int	command_pwd(void)
{
	int		exit;
	char	*str;

	exit = 0;
	str = getcwd(NULL, 0);
	printf("%s\n", str);
	free(str);
	return (exit);
}
