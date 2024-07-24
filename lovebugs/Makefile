# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ahashem <ahashem@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/31 17:51:32 by ahashem           #+#    #+#              #
#    Updated: 2024/07/24 20:23:13 by ahashem          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	minishell

LIBFT	=	ft_isprint.c ft_putchar_fd.c ft_strjoin.c \
			ft_strtrim.c ft_atoi.c ft_itoa.c \
			ft_putendl_fd.c ft_strlcat.c ft_substr.c \
			ft_bzero.c ft_putnbr_fd.c ft_strlcpy.c \
			ft_tolower.c ft_calloc.c  ft_memchr.c \
			ft_putstr_fd.c ft_strlen.c ft_toupper.c \
			ft_isalnum.c ft_memcmp.c ft_split.c \
			ft_strmapi.c ft_isalpha.c ft_memcpy.c \
			ft_strchr.c ft_strncmp.c ft_isascii.c \
			ft_memmove.c ft_strdup.c ft_strnstr.c \
			ft_isdigit.c ft_memset.c ft_striteri.c \
			ft_strrchr.c ft_realloc.c \
			fd_printf.c fd_parse.c fd_putchar.c \
			fd_putstr.c fd_put_hex.c fd_putnbr.c \
			fd_putnbr_u.c fd_put_address.c \
			ft_strcmp.c ft_strndup.c ft_strcat.c ft_strcpy.c ft_strjoin1.c

GNL		=	gnl/get_next_line_bonus.c gnl/get_next_line_utils_bonus.c

BLT		=	ft_cd.c ft_echo.c ft_env.c ft_exit.c ft_export.c ft_pwd.c ft_unset.c export_utils.c

SRCC	=	main.c arr_utils.c error.c builtins.c builtin_utils.c\
			parsing/parsing.c parsing/parse_tokens.c parsing/rename_tokens.c \
			parsing/join_tokens.c parsing/expand_var.c parsing/handle_quotes.c parsing/name_token.c \
			parsing/init_cmds.c parsing/init_redir.c parsing/init_env.c parsing/cmd_maker.c \
			execution/execution.c execution/exec_single.c execution/family.c \
			fd_close.c shell_handling.c freeing.c 
			

SRC 	= 	$(addprefix libft/, $(LIBFT)) $(GNL) $(addprefix srcs/, $(SRCC)) $(addprefix builtins/, $(BLT))

OBJ		=	$(SRC:.c=.o)

CFLAGS	=	-Wall -Wextra -Werror -fsanitize=address -g3

LRLFLAG =	-lreadline

all		:	$(NAME)

$(NAME)	:	$(OBJ) minishell.h
			cc $(CFLAGS) $(OBJ) $(LRLFLAG) -o $(NAME)

clean	:
			rm -rf $(OBJ)

fclean	:	clean
			rm -rf $(NAME)

re		:	fclean all

.PHONY	:	all clean fclean re

