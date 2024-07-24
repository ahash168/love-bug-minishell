/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahashem <ahashem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 12:22:10 by ahashem           #+#    #+#             */
/*   Updated: 2024/07/24 22:28:57 by ahashem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "./libft/libft.h"
# include "gnl/get_next_line_bonus.h"

# include <stdbool.h>
# include <curses.h>
# include <term.h>
# include <termios.h>
# include <sys/ioctl.h>
# include <string.h>
# include <dirent.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <signal.h>
# include <fcntl.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stddef.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
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

typedef struct sigaction	t_sigaction;

int							g_recived_signal;

typedef struct s_cmd
{
	char			**cmd;
	int				in;
	int				out;
	int				pid;
	struct s_cmd	*next;
	t_list			*args;
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
	int				exit_status;
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

void	init_env(char **env, t_env **my_env, t_mini *shell);

int		parsing(t_mini *shell);
void	name_token(char *input, t_token *token);
void	parse_tokens(t_mini *shell);
void	rename_tokens(t_mini *shell);
void	join_tokens(t_mini *shell);
void	expand_var(t_mini *shell);
void	print_tokens(t_token *head);
t_cmd	*cmd_maker(t_token *tokens);

void	quote_checker(t_mini *shell);
void	quote_remover(t_mini *shell);

void	init_cmds(t_mini *shell);
void	print_cmds(t_cmd *head);
void	init_redir(t_mini *shell);

int		execution(t_mini *shell);
char	**list_to_array(t_env *my_env);
void	exec_single(t_mini *shell, t_cmd *cmds);
void	set_redir(t_mini *shell, t_cmd *current);
char	**cmd_validator(char **cmd, char **env);

void	child(t_mini *shell, t_cmd *current);
void	parent(t_mini *shell, t_cmd *current);

int		is_builtin(char *input);
int		exec_builtin(t_mini *shell, t_cmd *cmds);

void	ft_exit_shell(t_mini *shell, int error, char *p_err, int fd);
void	free_shell(t_mini *shell);

void	free_s_cmd(t_cmd *cmds);
void	free_s_token(t_token *tokens);
void	free_s_env(t_env *env);

void	init_shell(t_mini *shell);
void	reset_shell(t_mini *shell);
void	free_shell(t_mini *shell);

void	init_sigaction(t_mini *shell);

# ifndef MAX_PATH
#  define MAX_PATH 256
# endif

# define BUFF_SIZE 4096
# define PWD_FAIL_CODE 2
# define ENV_FAIL_CODE 1
# define EXPORT_FAIL_CODE 1
# define EXPORT_FLAG 654
# define UNSET_FLAG 1
# define UNSET_FAIL_CODE 2
# define COMMAND_FAIL 127
# define EXIT_FAIL 1
# define EXIT_ALPHA_CODE 255
# define CD_FAIL 1
# define EXIST 0

int		g_exit_code;

int		ft_echo(char **input);
int		ft_env(t_env *my_env);
int		ft_pwd(void);
void	ft_cd(char **input, t_env *my_env);
char	*ft_getenv(char *key, t_env *my_env);
void	ft_exit(char **args, t_mini *mini);
void	ft_unset(char **args, t_mini *mini);
void	ft_export(char **args, t_mini *mini);
void	parse_new_export(char *arg, t_mini *mini);
void	ft_modify_env(char *arg, t_mini *mini);
t_env	*env_already_exist(char *arg, t_mini *mini);
int		check_export_args(char *arg);
int		check_valid_identifier(char *arg);
void	add_to_env(char *arg, t_mini *mini);
char	*set_env_value(char *arg, t_env *new);
char	*set_env_key(char *arg);
void	print_export(t_mini *mini);

#endif