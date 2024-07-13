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

void	handle_heredoc(t_cmd *cmd, char *delim)
{
	char	*line;
	int		tmp_fd;

	tmp_fd = open("tmp_file.tmp", O_RDWR | O_CREAT | O_TRUNC, 0600);
	while (1)
	{
		write(1, "> ", 2);
		line = get_next_line(0);
		if (!line)
			break ;
		if (!ft_strncmp(line, delim, ft_strlen(delim)))
		{
			free(line);
			break ;
		}
		write(tmp_fd, line, strlen(line));
        free(line);
	}
	close(tmp_fd);
	tmp_fd = open("tmp_file.tmp", O_RDONLY);
	unlink("tmp_file.tmp");
	cmd->in = tmp_fd;
}

void	fill_redir(t_cmd *cmd, t_token *token)
{
	int			fd;
	char		*str;

	str = token->str;
	if (token->next && token->next->type == SPACES)
		token = token->next;
	if (!ft_strncmp(str, ">>", 2))
	{
		if (cmd->out != 1 && cmd->out != -1)
			close(cmd->out);
		fd = open(token->next->str, O_WRONLY | O_CREAT | O_APPEND, 0644);
		printf("app: %d, file: %s\n", fd, token->next->str);
		cmd->out = fd;
	}
	else if (!ft_strncmp(str, "<<", 2))
	{
		printf("heredoc \n");
		handle_heredoc(cmd, token->next->str);
	}
	else if (!ft_strncmp(str, "<", 1))
	{
		if (cmd->in != 0 && cmd->in != -1)
			close(cmd->in);
		fd = open(token->next->str, O_RDONLY);
		printf("in: %d, file: %s\n", fd, token->next->str);
		cmd->in = fd;
	}
	else if (!ft_strncmp(str, ">", 1))
	{
		if (cmd->out != 1 && cmd->out != -1)
			close(cmd->out);
		fd = open(token->next->str, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		printf("out: %d, file: %s\n", fd, token->next->str);
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
		if (current_token && current_token->type == PIPE)
            current_token = current_token->next;
		current_cmd = current_cmd->next;
	}
	current_cmd = cmds;
	// while (current_cmd)
	// {
	// 	if (current_cmd->in != 0)
	// 		close(current_cmd->in);
	// 	if (current_cmd->out != 1)
	// 		close(current_cmd->out);
	// 	current_cmd = current_cmd->next;
	// }
}
