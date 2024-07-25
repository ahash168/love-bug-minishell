/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahashem <ahashem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 14:06:16 by bgordag           #+#    #+#             */
/*   Updated: 2024/07/25 22:16:26 by ahashem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	arg_count(char **args)
{
	int	i;

	i = 0;
	while (args[i] != NULL)
		i++;
	return (i);
}

int	check_exit_alpha(char **args)
{
	int	i;
	int	d;

	i = -1;
	while (args[++i] != NULL)
	{
		d = -1;
		while (args[i][++d] != '\0')
		{
			if (!ft_isdigit(args[i][d]))
			{
				fd_printf(2, "minishell: exit: %s: \
				numeric argument required\n", args[i]);
				return (1);
			}
		}
	}
	return (0);
}

void	ft_exit(char **args, t_mini *shell)
{
	int	code;

	code = 0;
	if (!args[1] && !shell->cmds->next)
		ft_exit_shell(shell, 0, "exit", 2);
	else if (!args[1])
		ft_exit_shell(shell, 0, NULL, 2);
	else if (ft_isdigit(args[1][0]) && arg_count(args) > 2)
	{
		fd_printf(2, "exit\n");
		fd_printf(2, "minishell: exit: too many arguments\n");
		shell->exit_status = 1;
		return ;
	}
	if (check_exit_alpha(&args[1]))
		code = 2;
	else
		code = ft_atoi(args[1]) % 256;
	if (shell->cmds->next)
		ft_exit_shell(shell, code, NULL, 2);
	else
		ft_exit_shell(shell, code, "exit", 2);
}
