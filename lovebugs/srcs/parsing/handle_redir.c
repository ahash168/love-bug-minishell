/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahashem <ahashem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 21:05:27 by ahashem           #+#    #+#             */
/*   Updated: 2024/07/26 00:30:13 by ahashem          ###   ########.fr       */
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
	if (cmd->in != 0 && cmd->in != -1)
		close(cmd->in);
	cmd->in = tmp_fd;
}

void	handle_infile(t_cmd *cmd, t_token *token)
{
	int	fd;

	if (cmd->in == -1 || cmd->out == -1)
		return ;
	if (cmd->in != 0)
		close(cmd->in);
	fd = open(token->next->str, O_RDONLY);
	cmd->in = fd;
}

void	handle_outfile(t_cmd *cmd, t_token *token)
{
	int	fd;

	if (cmd->in == -1 || cmd->out == -1)
		return ;
	if (cmd->out != 1)
		close(cmd->out);
	fd = open(token->next->str, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	cmd->out = fd;
}

void	handle_appendfile(t_cmd *cmd, t_token *token)
{
	int	fd;

	if (cmd->in == -1 || cmd->out == -1)
		return ;
	if (cmd->out != 1)
		close(cmd->out);
	fd = open(token->next->str, O_WRONLY | O_CREAT | O_APPEND, 0644);
	cmd->out = fd;
}
