/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgordag <mgordag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 22:40:57 by mgordag           #+#    #+#             */
/*   Updated: 2022/10/18 10:59:18 by mgordag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_redirection	*ft_lstlast_redir(t_redirection *redir)
{
	if (redir == NULL)
		return (0);
	while (redir->next != NULL)
		redir = redir->next;
	return (redir);
}

void	ft_lstadd_back_redir(t_redirection **redir, t_redirection *new)
{
	if (redir && new)
	{
		if (!*redir)
			*redir = new;
		else
			ft_lstlast_redir(*redir)-> next = new;
	}
}
