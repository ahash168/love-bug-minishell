/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: busragordag <busragordag@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 14:06:20 by bgordag           #+#    #+#             */
/*   Updated: 2024/06/23 23:04:30 by busragordag      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../builtins/builtins.h"

int	ft_pwd(void)
{
	char	cwd[MAX_PATH];

	getcwd(cwd, sizeof(cwd));
	printf("%s\n", cwd);
	return (0);
}
