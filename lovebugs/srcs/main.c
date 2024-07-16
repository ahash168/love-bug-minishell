/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahashem <ahashem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 12:34:07 by ahashem           #+#    #+#             */
/*   Updated: 2024/07/16 18:59:20 by ahashem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	init_shell(t_mini *shell)
{
	shell->input = NULL;
	shell->tokens = NULL;
	shell->cmds = NULL;
	shell->env_arr = NULL;
	shell->env_list = NULL;
	shell->cmd_count = 0;
	shell->pipe_fd[0] = 0;
	shell->pipe_fd[1] = 0;
	shell->prev_pipe = 0;
}

void	free_s_cmd(t_cmd *cmds)
{
	t_cmd	*current;
	t_cmd	*tmp;
	
	current = cmds;
	tmp = NULL;
	while (current)
	{
		tmp = current->next;
		if (current->cmd)
			freeer(current->cmd);
		free(current);
		current = tmp;
	}
}

void	free_s_token(t_token *tokens)
{
	t_token	*current;
	t_token	*tmp;
	
	current = tokens;
	tmp = NULL;
	while (current)
	{
		tmp = current->next;
		if (current->str)
			free(current->str);
		free(current);
		current = tmp;
	}
}

void	free_s_env(t_env *env)
{
	t_env	*current;
	t_env	*tmp;
	
	current = env;
	tmp = NULL;
	while (current)
	{
		tmp = current->next;
		if (current->var)
			free(current->var);
		if (current->value)
			free(current->value);
		free(current);
		current = tmp;
	}
}

void	reset_shell(t_mini *shell)
{
	if (shell->input)
		free(shell->input);
	if (shell->tokens)
		free_s_token(shell->tokens);
	// if (shell->cmds)
	// 	free_s_cmd(shell->cmds);
	// freeer(shell->env_arr);
	shell->cmd_count = 0;
	shell->pipe_fd[0] = 0;
	shell->pipe_fd[1] = 0;
	shell->prev_pipe = 0;
}

int	main(int ac, char **av, char **env)
{
	t_mini	*shell;

	(void) av;
	if (ac != 1 || !*env)
		return (1);
	shell = ft_calloc(1, sizeof(t_mini));
	init_shell(shell);
	init_env(env, &(shell->env_list));
	while (1)
	{
		shell->input = readline("minishell> ");
		if (!shell->input)
			break ;
		if (*shell->input)
		{
			add_history(shell->input);
			if (!parsing(shell))
			{
				execution(shell->cmds, shell->env_list);
			}
			reset_shell(shell);
		}
		// free(shell->input);
	}
	free_s_env(shell->env_list);
	return (0);
}
