/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahashem <ahashem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 14:21:00 by ahashem           #+#    #+#             */
/*   Updated: 2024/07/25 23:24:11 by ahashem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	parsing(t_mini *shell)
{
	if (quote_checker(shell))
	{
		shell->exit_status = 1;
		return (shell->exit_status);
	}
	if (tokenizer(shell))
	{
		shell->exit_status = 1;
		return (shell->exit_status);
	}
	if (parse_tokens(shell))
	{
		shell->exit_status = 258;
		return (shell->exit_status);
	}
	join_tokens(shell);
	rename_tokens(shell);
	expand_var(shell);
	quote_remover(shell);
	init_cmds(shell);
	init_redir(shell);
	return (0);
}
