/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahashem <ahashem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 12:22:10 by ahashem           #+#    #+#             */
/*   Updated: 2024/07/16 18:44:54 by ahashem          ###   ########.fr       */
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
	int				prev_pipe;
}					t_mini;

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

int		parsing(t_mini *shell);
void	parse_tokens(t_mini *shell);
void	rename_tokens(t_token *tokens);
void	join_tokens(t_token *tokens);
void	expand_var(t_token *tokens);
void	print_tokens(t_token *head);

void	quote_checker(t_mini *shell);
void	quote_remover(t_token *tokens);

t_cmd	*init_cmds(t_token *tokens);
void	print_cmds(t_cmd *head);
void	init_redir(t_cmd *cmds, t_token *tokens);

int		execution(t_cmd *cmds, t_env *my_env);
void	exec_single(t_cmd *cmd, t_env *my_env, char **env);
void	set_redir(t_cmd *cmd);

#endif
