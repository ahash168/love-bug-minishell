/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: busragordag <busragordag@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 14:13:25 by bgordag           #+#    #+#             */
/*   Updated: 2024/06/23 22:51:39 by busragordag      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "../minishell.h"
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <errno.h>
# include <sys/wait.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>

# include <string.h>
# include <limits.h>
# include <ctype.h>

#ifndef MAX_PATH
# define MAX_PATH 256
#endif

// typedef struct s_env
// {
// 	char			*var;
// 	char			*value;
// 	struct s_env	*next;
// }			t_env;


int		ft_echo(char **input);
int		ft_env(t_env *our_env);
int		ft_pwd(void);

#endif
