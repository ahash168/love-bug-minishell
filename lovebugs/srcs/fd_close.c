/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_close.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahashem <ahashem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 15:17:01 by ahashem           #+#    #+#             */
/*   Updated: 2024/07/24 16:25:03 by ahashem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_close(int fd, int limit, t_cmd *cmd)
{
	int	ret;

	if (fd >= limit)
	{
		ret = close(fd);
		if (ret == -1)
		{
			if (cmd && cmd->cmd[0])
				fd_printf(2, "error closing fd %d in %s\n", fd, cmd->cmd[0]);
			else
				fd_printf(2, "error closing fd %d\n", fd);
		}
		else
			return (-2);
	}
	return (-2);
}

void	ft_exit_shell(t_mini *shell, int error, char *p_err, int fd)
{
	g_exit_code = error;
	if (p_err)
		fd_printf(fd, "%s\n", p_err);
	free_shell(shell);
	ft_close(0, 0, NULL);
	ft_close(1, 0, NULL);
	ft_close(2, 0, NULL);
	exit(g_exit_code);
}

// void close_all_fds(t_mini *mini)
// {
// 	t_cmd *cmd;
// 	t_rdr *rdr;

// 	cmd = mini->l_cmd;
// 	while (cmd)
// 	{
// 		rdr = cmd->rdr;
// 		if (rdr)
// 		{
// 			while (rdr)
// 			{
// 				rdr->dup2_fd = ft_close(rdr->dup2_fd, 3, cmd);
// 				rdr->fd = ft_close(rdr->fd, 3, cmd);
// 				rdr->fdpipe[0] = ft_close(rdr->fdpipe[0], 3, cmd);
// 				rdr->fdpipe[1] = ft_close(rdr->fdpipe[1], 3, cmd);
// 				rdr->og_fd = ft_close(rdr->og_fd, 3, cmd);
// 				rdr = rdr->next;
// 			}
// 		}
// 		cmd = cmd->next;
// 	}
// }