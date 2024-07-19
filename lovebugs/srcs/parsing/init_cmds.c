/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahashem <ahashem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 14:15:07 by ahashem           #+#    #+#             */
/*   Updated: 2024/07/19 18:35:37 by ahashem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	print_cmds(t_cmd *head)
{
	int		i = 1;
	t_cmd	*current = head;

	while (current != NULL)
	{
		i = 1;
		printf("\nCMD: %s$\n", current->cmd[0]);
		while (current->cmd[i] != NULL)
			printf("ARG: %s$\n", current->cmd[i++]);
		printf("IN: %d\tOUT: %d\n", current->in, current->out);
		current = current->next;
	}
	printf("\n");
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
		if (current->type == CMD || current->type == ARG)
			i++;
		current = current->next;
	}
	cmd->cmd = ft_calloc(i + 1, sizeof(char *));
	current = token;
	i = 0;
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
	// print_cmds(cmds);
}
