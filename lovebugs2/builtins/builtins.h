/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgordag <bgordag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 14:13:25 by bgordag           #+#    #+#             */
/*   Updated: 2024/06/20 14:45:53 by bgordag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "../libft/libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <errno.h>
# include <sys/wait.h>
# include <errno.h>
#include <readline/readline.h>
#include <readline/history.h>

# include <string.h>
# include <limits.h>
# include <ctype.h>

int		ft_echo(char *input);
int		ft_env(char **our_env);
int		ft_pwd(void);

#endif
