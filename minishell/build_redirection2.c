/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_redirection2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgordag <mgordag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 22:38:51 by mgordag           #+#    #+#             */
/*   Updated: 2022/10/17 22:38:54 by mgordag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_arger(char **cmd, int idx)
{
	if (is_redir(&cmd[0][idx]))
	{
		g_data.syntax_err = 1;
		return (0);
	}
	else if (cmd[0][idx] != ' ')
		return (1);
	return (0);
}
