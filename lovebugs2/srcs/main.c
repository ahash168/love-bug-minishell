/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahashem <ahashem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 12:34:07 by ahashem           #+#    #+#             */
/*   Updated: 2024/06/20 13:00:37 by ahashem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_env(char **our_env)
{
	int	i;

	i = 0;
	while (our_env[i])
		printf("%s\n", our_env[i++]);
}

int	ft_echo(char *input)
{
	int	i;
	int	j;
	int	check;
	char	**split_input;

	i = 0;
	check = 1;
	split_input = ft_split(input, ' ');
	while (split_input[++i] && ft_strncmp(split_input[i], "-n", 2) == 0)
	{
		j = 2;
		if (split_input[i][j] == '\0')
			check = 0;
		while (split_input[i][j])
		{
			if (split_input[i][j++] == 'n')
				check = 0;
			else
			{
				check = 1;
				printf("%s ", split_input[i]);
			}
		}
	}
	while (split_input[i] && i < arrlen(split_input) - 1)
		printf("%s ", split_input[i++]);
	printf("%s", split_input[i]);
	if (check)
		printf("\n");
	freeer(split_input);
	return (0);
}

char	**init_env(char **env)
{
	return (arrcopy(env));
}

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
}

int main(int ac, char **av, char **env)
{
	char *input;
	char **our_env;
	
	(void) ac;
	(void) av;
	our_env = init_env(env);
    while (1) {
        input = readline("minishell> ");
        if (!input) {
            break; // Handle EOF (Ctrl+D)
        }
        if (*input) {
            add_history(input);
			if (builtin_input(input) == 0)
				exec_builtin(input, our_env);
            // Parse and execute input
        }
        free(input);
    }
	freeer(our_env);
    return (0);
}