/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_maker.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahashem <ahashem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 20:08:45 by ahashem           #+#    #+#             */
/*   Updated: 2024/07/24 20:25:38 by ahashem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	cmd_loop(t_token *token, t_cmd *cmd, int count)
{
	int		i;
	int		j;
	t_token	*current;

	i = 0;
	j = 1;
	current = token;
	cmd->cmd = ft_calloc(count + 1, sizeof(char *));
	while (current && current->type != PIPE)
	{
		if (current->type == CMD)
			cmd->cmd[0] = ft_strdup(current->str);
		else if (current->type == ARG)
			cmd->cmd[j++] = ft_strdup(current->str);
		current = current->next;
		i++;
	}
	if (cmd->cmd && cmd->cmd[0])
		cmd->cmd[j] = NULL;
	return (i);
}

int	fill_cmd(t_token *token, t_cmd *cmd)
{
	int		count;
	t_token	*current;

	count = 0;
	current = token;
	while (current && current->type != PIPE)
	{
		if (current->type == CMD || current->type == ARG)
			count++;
		current = current->next;
	}
	return (cmd_loop(token, cmd, count));
}

t_cmd	*cmd_maker(t_token *tokens)
{
	int		i;
	t_token	*token;
	t_cmd	*cmds_list;
	t_cmd	*current_cmd;
	t_cmd	*last_cmd;

	token = tokens;
	cmds_list = NULL;
	last_cmd = NULL;
	while (token)
	{
		current_cmd = ft_calloc(1, sizeof(t_cmd));
		i = fill_cmd(token, current_cmd);
		if (!cmds_list)
			cmds_list = current_cmd;
		else
			last_cmd->next = current_cmd;
		last_cmd = current_cmd;
		while (token && i-- > 0)
			token = token->next;
		if (token && token->type == PIPE)
			token = token->next;
	}
	last_cmd->next = NULL;
	return (cmds_list);
}
