/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: busragordag <busragordag@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 14:06:18 by bgordag           #+#    #+#             */
/*   Updated: 2024/07/23 18:31:37 by busragordag      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	swap_content(t_list *a, t_list *b)
{
	void	*temp;

	temp = a->content;
	a->content = b->content;
	b->content = temp;
}

int	check_export_args(char *arg)
{
	if (!arg || !arg[0] || check_valid_identifier(arg))
	{
		g_exit_code = EXPORT_FLAG;
		return (1);
	}
	return (0);
}

t_env	*env_already_exist(char *arg, t_mini *mini)
{
	t_env	*temp;
	size_t	i;

	i = 0;
	while (arg[i] != '\0' && arg[i] != '=')
		i++;
	temp = mini->env_list;
	while (temp)
	{
		if (0 == ft_strncmp(temp->var, arg, i)
			&& ft_strlen(temp->var) == i)
			return (temp);
		temp = temp->next;
	}
	return (NULL);
}

void	ft_modify_env(char *arg, t_mini *mini)
{
	t_env	*temp;
	char	*new_value;
	size_t	i;

	new_value = ft_strchr(arg, '=');
	if (new_value == NULL)
		return ;
	i = 0;
	while (arg[i] && arg[i] != '=')
		i++;
	temp = mini->env_list;
	while (temp)
	{
		if (0 == ft_strncmp(temp->var, arg, i)
			&& ft_strlen(temp->var) == i)
			break ;
		temp = temp->next;
	}
	free(temp->value);
	new_value++;
	temp->init = 1;
	temp->value = ft_strdup(new_value);
}

void	parse_new_export(char *arg, t_mini *mini)
{
	if (!env_already_exist(arg, mini))
		add_to_env(arg, mini);
	else
		ft_modify_env(arg, mini);
}

void	ft_export(char **args, t_mini *mini)
{
	int		i;

	i = 0;
	if (!mini->env_list)
	{
		fd_printf(2, "export: permission denied\n");
		return ;
	}
	if (!args[1])
	{
		print_export(mini);
		return ;
	}
	while (args[++i] != NULL)
	{
		if (check_export_args(args[i]))
			fd_printf(2, "minishell: export: `%s': not a valid identifier\n",
				args[i]);
		else
			parse_new_export(args[i], mini);
	}
	if (g_exit_code == EXPORT_FLAG)
		g_exit_code = EXPORT_FAIL_CODE;
	else
		g_exit_code = 0;
} 