/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgordag <bgordag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 14:02:43 by bgordag           #+#    #+#             */
/*   Updated: 2024/06/20 14:48:35 by bgordag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	builtin_input(char *input)
{
	int	builtin;

	builtin = 1;
	if (ft_strncmp(input, "echo", 4) == 0 || ft_strncmp(input, "cd", 2) == 0
	|| ft_strncmp(input, "pwd", 3) == 0 || ft_strncmp(input, "export", 6) == 0
	|| ft_strncmp(input, "unset", 5) == 0 || ft_strncmp(input, "env", 3) == 0
	|| ft_strncmp(input, "exit", 4) == 0)
		builtin = 0;
	return (builtin);
}

void	exec_builtin(char *input, char **env)
{
	if (ft_strncmp(input, "echo", 4) == 0)
		ft_echo(input);
	if (ft_strncmp(input, "env", 3) == 0)
		ft_env(env);
	if (ft_strncmp(input, "pwd", 3) == 0)
		ft_pwd();
}
