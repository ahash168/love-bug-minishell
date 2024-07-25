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
	char		*str;

	str = token->str;
	if (token->next && token->next->type == SPACES)
		token = token->next;
	if (!ft_strncmp(str, ">>", 2))
		handle_appendfile(cmd, token);
	else if (!ft_strncmp(str, "<<", 2))
		handle_heredoc(cmd, token->next->str);
	else if (!ft_strncmp(str, "<", 1))
		handle_infile(cmd, token);
	else if (!ft_strncmp(str, ">", 1))
		handle_outfile(cmd, token);
}

void	init_redir(t_mini *shell)
{
	t_cmd	*current_cmd;
	t_token	*current_token;

	current_cmd = shell->cmds;
	current_token = shell->tokens;
	while (current_cmd)
	{
		while (current_token && current_token->type != PIPE)
		{
			if (current_token->type == REDIR)
				fill_redir(current_cmd, current_token);
			current_token = current_token->next;
		}
		if (current_token && current_token->type == PIPE)
			current_token = current_token->next;
		current_cmd = current_cmd->next;
	}
}
