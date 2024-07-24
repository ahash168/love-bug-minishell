# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: busragordag <busragordag@student.42.fr>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/30 13:44:46 by ahashem           #+#    #+#              #
#    Updated: 2024/07/21 23:24:47 by busragordag      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	libft.a

SRC 	= 	ft_isprint.c ft_putchar_fd.c ft_strjoin.c ft_strtrim.c ft_atoi.c \
			ft_itoa.c ft_putendl_fd.c ft_strlcat.c ft_substr.c ft_bzero.c \
			ft_putnbr_fd.c ft_strlcpy.c ft_tolower.c ft_calloc.c  ft_memchr.c \
			ft_putstr_fd.c ft_strlen.c ft_toupper.c ft_isalnum.c  ft_memcmp.c \
			ft_split.c ft_strmapi.c ft_isalpha.c  ft_memcpy.c ft_strchr.c \
			ft_strncmp.c ft_isascii.c ft_memmove.c ft_strdup.c ft_strnstr.c \
			ft_isdigit.c ft_memset.c ft_striteri.c ft_strrchr.c ft_strcmp.c \
			ft_strndup.c ft_strcat.c ft_strcpy.c ft_strjoin1.c

BONUS	=	ft_lstmap.c ft_lstnew.c ft_lstadd_back.c ft_lstsize.c ft_lstadd_front.c \
			ft_lstdelone.c ft_lstiter.c ft_lstlast.c ft_lstclear.c

OBJ		=	$(SRC:.c=.o)

BONUSO	=	$(BONUS:.c=.o)

CFLAGS	=	-Wall -Wextra -Werror

all		:	$(NAME)

$(NAME)	:	$(OBJ)
			ar -rcs $(NAME) $(OBJ)

bonus	:	$(OBJ) $(BONUSO)
			ar -rcs $(NAME) $(OBJ) $(BONUSO)
			
clean	:
			rm -rf $(OBJ)
			rm -rf $(BONUSO)

fclean	:	clean
			rm -rf $(NAME)

re		:	fclean all

.PHONY	:	all clean fclean re
