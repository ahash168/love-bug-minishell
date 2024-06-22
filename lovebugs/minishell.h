/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahashem <ahashem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 12:22:10 by ahashem           #+#    #+#             */
/*   Updated: 2024/06/22 12:24:05 by ahashem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "./libft/libft.h"
# include "./builtins/builtins.h"
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


typedef struct s_env
{
	char			*var;
	char			*value;
	struct s_env	*next;
}			t_env;

char	**arrcopy(char **arr);
int		arrlen(char **arr);

char	**freeer(char **arr);
void	error_message(int n);
void	errorer(void *ptr, int dimension, int n);

int		builtin_input(char *input);
int		exec_builtin(char **input, t_env *env);

int		line_count(char *map_str);
int		ft_strset(char strc, char *set);
int		strchar_count(char *str, char c);

#endif
