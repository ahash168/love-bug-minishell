/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahashem <ahashem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 14:15:07 by ahashem           #+#    #+#             */
/*   Updated: 2024/07/24 20:08:55 by ahashem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	std_inout(t_cmd *cmds)
{
	t_cmd	*current;

	current = cmds;
	while (current)
	{
		current->in = 0;
		current->out = 1;
		current = current->next;
	}
}

int	cmd_count(t_cmd *cmds)
{
	int	i;

	i = 0;
	while (cmds)
	{
		i++;
		cmds = cmds->next;
	}
	return (i);
}

void	init_cmds(t_mini *shell)
{
	shell->cmds = cmd_maker(shell->tokens);
	shell->cmd_count = cmd_count(shell->cmds);
	std_inout(shell->cmds);
}
