/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahashem <ahashem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 14:06:20 by bgordag           #+#    #+#             */
/*   Updated: 2024/07/14 13:07:44 by ahashem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../builtins/builtins.h"

int	ft_pwd(void)
{
	char	cwd[MAX_PATH];

	getcwd(cwd, sizeof(cwd));
	ft_putendl_fd(cwd, 1);
	return (0);
}
