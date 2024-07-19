/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahashem <ahashem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 12:22:10 by ahashem           #+#    #+#             */
/*   Updated: 2024/07/19 11:06:52 by ahashem          ###   ########.fr       */
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

#define RESET "\033[0m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN "\033[36m"
#define BOLD "\033[1m"
#define UNDERLINE "\033[4m"

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
	// int				count;
	int				pid;
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

typedef struct s_mini
{
	char			*input;
	struct s_token	*tokens;
	struct s_cmd	*cmds;
	int				cmd_count;
	char			**env_arr;
	struct s_env	*env_list;
	int				pipe_fd[2];
}					t_mini;

char	**arrcopy(char **arr);
int		arrlen(char **arr);

char	**freeer(char **arr);
void	error_message(int n);
void	errorer(void *ptr, int dimension, int n);

int		line_count(char *map_str);
int		ft_strset(char *str, char *set);
int		ft_charset(char strc, char *set);
int		strchar_count(char *str, char c);

void	init_env(char **env, t_env **my_env);

int		parsing(t_mini *shell);
void	parse_tokens(t_mini *shell);
void	rename_tokens(t_mini *shell);
void	join_tokens(t_mini *shell);
void	expand_var(t_mini *shell);
void	print_tokens(t_token *head);

void	quote_checker(t_mini *shell);
void	quote_remover(t_mini *shell);

void	init_cmds(t_mini *shell);
void	print_cmds(t_cmd *head);
void	init_redir(t_mini *shell);

int		execution(t_mini *shell);
void	exec_single(t_mini *shell);
void	exec_multiple(t_cmd *cmd, t_env *my_env, char **env);
void	set_redir(t_cmd *cmd);
char	**cmd_validator(char **cmd, char **env);

int		is_builtin(char *input);
int		exec_builtin(char **cmd_arg, t_env *env);

#endif
