/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahashem <ahashem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 12:34:07 by ahashem           #+#    #+#             */
/*   Updated: 2024/07/12 22:32:29 by ahashem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	**add_basic_env(t_mini *shell)
{
	char	**env;
	char	cwd[2056];
	char	*pwd;
	char	*full_env;

	ft_bzero(cwd, sizeof(cwd));
	if (getcwd(cwd, sizeof(cwd)) != NULL)
		pwd = ft_strjoin1("PWD=", cwd);
	else
		return (NULL);
	full_env = ft_strjoin1(pwd, " SHLVL=0 _=/usr/bin/env");
	if (!full_env)
		return (NULL);
	free(pwd);
	env = ft_split(full_env, ' ');
	if (!env)
		ft_exit_shell(shell, 1, "add_basic_env", 2);
	free(full_env);
	return (env);
}

void	increase_shlvl(t_env *my_env, t_mini *shell)
{
	char	*args_str;
	char	**args;
	int		level;

	args_str = NULL;
	args = NULL;
	args_str = malloc(sizeof(char) * 17);
	args_str = ft_strdup("export SHLVL=");
	if (ft_getenv("SHLVL", my_env) == NULL)
		args_str = ft_strjoin(args_str, "1", 1);
	else
	{
		level = ft_atoi(ft_getenv("SHLVL", my_env)) + 1;
		if (level >= 1000)
			level = 0;
		args_str = ft_strjoin(args_str, ft_itoa(level), 1);
	}
	args_str[ft_strlen(args_str)] = '\0';
	args = ft_split(args_str, ' ');
	free(args_str);
	ft_export(args, shell);
	freeer(args);
}

void	init_env(char **env, t_env **my_env, t_mini *shell)
{
	int		i;
	t_env	*new_var;
	t_env	*last_var;

	if (!env || !env[0])
		env = add_basic_env(shell);
	i = 0;
	last_var = NULL;
	while (env[i])
	{
		new_var = (t_env *) ft_calloc(1, sizeof(t_env));
		new_var->var = ft_substr(env[i], 0, ft_strchr(env[i], '=') - env[i]);
		new_var->value = ft_strdup(ft_strchr(env[i], '=') + 1);
		new_var->init = 1;
		new_var->next = NULL;
		if (!(*my_env))
			*my_env = new_var;
		else
			last_var->next = new_var;
		last_var = new_var;
		i++;
	}
	last_var->next = NULL;
	increase_shlvl(*my_env, shell);
}
