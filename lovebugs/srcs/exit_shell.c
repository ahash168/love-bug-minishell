/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahashem <ahashem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 15:17:01 by ahashem           #+#    #+#             */
/*   Updated: 2024/07/25 23:26:01 by ahashem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_exit_shell(t_mini *shell, int error, char *p_err, int fd)
{
	int	status;

	status = 0;
	shell->exit_status = error;
	if (p_err)
		fd_printf(fd, "%s\n", p_err);
	status = shell->exit_status;
	free_shell(shell);
	exit(status);
}
