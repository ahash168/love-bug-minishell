/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahashem <ahashem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 14:06:22 by bgordag           #+#    #+#             */
/*   Updated: 2024/07/25 22:14:47 by ahashem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_valid_identifier_export(char *arg)
{
	int		i;
	size_t	d;

	d = 0;
	i = 0;
	if (arg[0] && ft_isdigit(arg[0]))
		return (1);
	while (arg[i] != '\0')
	{
		if (!ft_isalnum(arg[i]) && arg[i] != '_')
			d++;
		i++;
	}
	if (d)
		return (1);
	else
		return (0);
}

int	check_unset_args(char *arg, t_mini *shell)
{
	if (!arg || !arg[0] || check_valid_identifier_export(arg))
	{
		shell->exit_status = UNSET_FLAG;
		return (1);
	}
	return (0);
}

void	free_single_env(t_env *node)
{
	free(node->var);
	free(node->value);
	free(node);
}

void	delete_env_list(char *arg, t_mini *mini)
{
	t_env	*temp;
	t_env	*prev;

	if (!mini->env_list)
		return ;
	temp = mini->env_list;
	if (temp != NULL && ft_strncmp(temp->var, arg, strlen(arg) + 1) == 0)
	{
		mini->env_list = temp->next;
		free_single_env(temp);
		return ;
	}
	prev = NULL;
	while (temp != NULL && ft_strncmp(arg, temp->var, strlen(arg) + 1))
	{
		prev = temp;
		temp = temp->next;
	}
	if (!temp)
		return ;
	if (prev)
		prev->next = temp->next;
	free_single_env(temp);
}

void	ft_unset(char **args, t_mini *shell)
{
	int	i;

	i = 1;
	if (!args[1])
	{
		shell->exit_status = 0;
		return ;
	}
	while (args[i] != NULL)
	{
		if (check_unset_args(args[i], shell))
			fprintf(stderr, "minishell: unset: `%s': \
			not a valid identifier\n", args[i]);
		else
			delete_env_list(args[i], shell);
		i++;
	}
	if (shell->exit_status == UNSET_FLAG)
		shell->exit_status = UNSET_FAIL_CODE;
	else
		shell->exit_status = 0;
}
