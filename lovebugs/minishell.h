/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahashem <ahashem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 12:22:10 by ahashem           #+#    #+#             */
/*   Updated: 2024/07/13 22:45:17 by ahashem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "./libft/libft.h"
// # include "./builtins/builtins.h"
# include "gnl/get_next_line_bonus.h"
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

enum e_type
{
	SPACES,
	WORD,
	CMD,
	PATH,
	ARG,
	PIPE,
	REDIR,
	SINGLE,
	DOUBLE,
	VAR,
	DELIM
};

typedef struct s_cmd
{
	char			**cmd;
	int				in;
	int				out;
	int				count;
	struct s_cmd	*next;
}					t_cmd;

typedef struct s_token
{
	enum e_type		type;
	char			*str;
	struct s_token	*next;
}					t_token;

typedef struct s_env
{
	char			*var;
	char			*value;
	int				init;
	struct s_env	*next;
}			t_env;

char	**arrcopy(char **arr);
int		arrlen(char **arr);

char	**freeer(char **arr);
void	error_message(int n);
void	errorer(void *ptr, int dimension, int n);

int		is_builtin(char *input);
int		exec_builtin(char **cmd_arg, t_env *env);

int		line_count(char *map_str);
int		ft_strset(char strc, char *set);
int		strchar_count(char *str, char c);

// void	execute_commands(t_parsed_commands parsed_commands, t_env *my_env);
// void	execute(char **command, int input_file, int output_file, t_env *my_env);
void	init_env(char **env, t_env **my_env);

t_cmd	*parsing(char *input);
void	parse_tokens(t_token *tokens);
void	rename_tokens(t_token *tokens);
void	join_tokens(t_token *tokens);
void	expand_var(t_token *tokens);
void	print_tokens(t_token *head);

void	quote_checker(char *input);
void	quote_remover(t_token *tokens);

t_cmd	*init_cmds(t_token *tokens);
void	print_cmds(t_cmd *head);
void	init_redir(t_cmd *cmds, t_token *tokens);

void	exec_cmds(t_cmd *cmds, t_env *my_env);

#endif
