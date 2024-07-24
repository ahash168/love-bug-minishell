/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahashem <ahashem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 14:06:09 by bgordag           #+#    #+#             */
/*   Updated: 2024/07/24 15:55:09 by ahashem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_getenv(char *key, t_env *my_env)
{
	t_env	*current;

	current = my_env;
	while (current)
	{
		if (strncmp(current->var, key, ft_strlen(key)) == 0)
			return (current->value);
		current = current->next;
	}
	return (NULL);
}

void	go_to_old_pwd(t_env *my_env)
{
	char	*old_path;

	old_path = ft_getenv("OLDPWD", my_env);
	if (!old_path)
	{
		printf("minishell: cd: OLDPWD not set\n");
		return ;
	}
	ft_putendl_fd(old_path, 1);
	chdir(old_path);
}

void	go_to_home(t_env *my_env)
{
	char	*path;

	path = ft_getenv("HOME", my_env);
	if (!path)
	{
		printf("minishell: cd: HOME not set\n");
		return ;
	}
	chdir(path);
}

void	ft_cd(char **input, t_env *my_env)
{
	(void) my_env;
	if (!input[1] || !ft_strncmp(input[1], "~", 2))
		go_to_home(my_env);
	else if (strcmp(input[1], "-") == 0)
		go_to_old_pwd(my_env);
	else
		chdir(input[1]);
}
