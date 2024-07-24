#include "../minishell.h"

void	print_export(t_mini *mini)
{
	t_env	*env;

	env = mini->env_list;
	if (!env)
	{
		fd_printf(2, "env: permission denied\n");
		g_exit_code = ENV_FAIL_CODE;
		return ;
	}
	while (env)
	{
		if (env->init)
		{
			if (env->value == NULL)
				fd_printf(1, "declare -x %s=\"\"\n", env->var, env->value);
			else
				fd_printf(1, "declare -x %s=\"%s\"\n", env->var, env->value);
		}
		else
			fd_printf(1, "declare -x %s\n", env->var);
		env = env->next;
	}
	g_exit_code = 0;
}

char	*set_env_key(char *arg)
{
	int		i;
	char	*new_key;

	i = 0;
	while (arg[i] != '\0' && arg[i] != '=')
		i++;
	new_key = ft_calloc(1, i + 1);
	i = 0;
	while (arg[i] != '\0' && arg[i] != '=')
	{
		new_key[i] = arg[i];
		i++;
	}
	new_key[i] = '\0';
	return (new_key);
}

char	*set_env_value(char *arg, t_env *new)
{
	char	*value;

	value = ft_strchr(arg, '=');
	if (value == NULL)
	{
		new->init = 0;  // initialised yerine init
		return (ft_strdup(""));
	}
	else
	{
		new->init = 1;  // initialised yerine init
		value++;
		return (ft_strdup(value));
	}
}

void	add_to_env(char *arg, t_mini *mini)
{
	t_env	*temp;
	t_env	*new;

	temp = mini->env_list;
	new = ft_calloc(1, sizeof(t_env));
	new->next = NULL;
	new->value = set_env_value(arg, new);
	new->var = set_env_key(arg);  // key yerine var
	if (temp == NULL)
	{
		mini->env_list = new;
	}
	else
	{
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new;
	}
}

int	check_valid_identifier(char *arg)
{
	int		i;
	size_t	d;

	d = 0;
	i = -1;
	if ((arg[0] && ft_isdigit(arg[0])) || arg[0] == '=')
		return (1);
	while (arg[++i] != '\0' && arg[i] != '=')
		if (!ft_isalnum(arg[i]) && arg[i] != '_')
			d++;
	if (d)
		return (1);
	else
		return (0);
}