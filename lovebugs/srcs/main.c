/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahashem <ahashem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 12:34:07 by ahashem           #+#    #+#             */
/*   Updated: 2024/06/22 14:47:08 by ahashem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	init_env(char **env, t_env **my_env)
{
    int     i;
    t_env   *new_var;
	t_env	*last_var;

    if (!env || !env[0])
        return ;
	i = 0;
	my_env = NULL;
	last_var = NULL;
    while (env[i])
    {
		new_var = (t_env *) ft_calloc(1, sizeof(t_env));
        new_var->var = ft_substr(env[i], 0, ft_strchr(env[i], '=') - env[i]);
        new_var->value = ft_strdup(ft_strchr(env[i], '=') + 1);
		new_var->next = NULL;
		if (!my_env)
			my_env = &new_var;
		else
			last_var->next = new_var;
		last_var = new_var;
		i++;
    }
}

int main(int ac, char **av, char **env)
{
    // char *input;
    t_env *my_env;
    // char **split_input;
    
    (void) ac;
    (void) av;
    init_env(env, &my_env);
    // split_input = NULL;
    // while (1) {
    //     input = readline("minishell> ");
    //     if (!input) {
    //         break; // Handle EOF (Ctrl+D)
    //     }
    //     if (*input) {
    //         add_history(input);
    //         split_input = ft_split(input, ' ');
    //         if (builtin_input(split_input[0]) == 0)
    //             exec_builtin(split_input, my_env);
    //         // Parse and execute input
    //     }
    //     free(input);
    // }
    // freeer(my_env);
    return (0);
}
