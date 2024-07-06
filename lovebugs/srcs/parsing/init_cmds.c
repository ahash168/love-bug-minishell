/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahashem <ahashem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 14:15:07 by ahashem           #+#    #+#             */
/*   Updated: 2024/07/04 18:49:34 by ahashem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	print_cmds(t_cmd *head)
{
	int		i = 1;
	int		x = 0;
	t_cmd	*current = head;
	
	while (current != NULL)
	{
		printf("x: %d\n", x);		
		i = 1;
		printf("CMD: %s$\n", current->cmd[0]);
		while (current->cmd[i] != NULL)
			printf("ARG: %s$\n", current->cmd[i++]);
		current = current->next;
		x++;
	}
}

int	fill_cmd(t_token *token, t_cmd *cmd)
{
	int		i;
	int		j;
	t_token	*current;

	i = 0;
	j = 1;
	current = token;
	while (current && current->type != PIPE)
	{
		current = current->next;
		i++;
	}
	cmd->cmd = ft_calloc(i + 1, sizeof(char *));
	current = token;
	while (current && current->type != PIPE)
	{
		if (current->type == CMD)
			cmd->cmd[0] = current->str;
		else if (current->type == ARG)
			cmd->cmd[j++] = current->str;
		// else if (current->type == SPACES)
		// 	cmd->cmd[j++] = current->str;
		current = current->next;
	}
	cmd->cmd[j] = NULL;
	return (i);
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
	return (cmds_list);
}

void	init_cmds(t_token *tokens)
{
	t_cmd	*cmds;
	
	cmds = NULL;
	cmds = cmd_maker(tokens);
	print_cmds(cmds);
}
