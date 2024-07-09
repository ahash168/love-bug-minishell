/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahashem <ahashem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 15:08:51 by ahashem           #+#    #+#             */
/*   Updated: 2024/07/09 15:08:51 by ahashem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	fill_redir(t_cmd *cmd, t_token *token)
{
	int			fd;

	if (!ft_strncmp(token->str, "<", 1))
	{
		fd = open(token->next->str, O_RDONLY);
		printf("in %d\n", fd);
		if (cmd->in != 0 && cmd->in != -1)
			close(fd);
		cmd->in = fd;
	}
	else if (!ft_strncmp(token->str, ">", 1))
	{
		fd = open(token->next->str, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		printf("out %d\n", fd);
		if (cmd->in != 1 && cmd->in != -1)
			close(fd);
		cmd->out = fd;
	}
	else if (!ft_strncmp(token->str, ">>", 1))
	{
		fd = open(token->next->str, O_WRONLY | O_CREAT | O_APPEND, 0644);
		printf("append %d\n", fd);
		if (cmd->in != 1 && cmd->in != -1)
			close(fd);
		cmd->out = fd;
	}
}

void	init_redir(t_cmd *cmds, t_token *tokens)
{
	t_cmd	*current_cmd;
	t_token	*current_token;

	current_cmd = cmds;
	current_token = tokens;
	while (current_cmd)
	{
		while (current_token && current_token->type != PIPE)
		{
			if (current_token->type == REDIR)
				fill_redir(current_cmd, current_token);
			current_token = current_token->next;
		}
		current_cmd = current_cmd->next;
	}

}