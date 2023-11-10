# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: xortega <xortega@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/25 12:09:10 by xortega           #+#    #+#              #
#    Updated: 2023/11/10 15:35:22 by xortega          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME := pipex
SOURCES :=	pipex.c
CC				:= gcc
CFLAGS			:= -Wall -Wextra -Werror

.SILENT:

all: $(NAME)

$(NAME):
	$(CC) $(CFLAGS) pipex.c pipex_get_argv.c pipex_get_path.c libft.a -o $(NAME)
	chmod 777 $(NAME)

fclean:
	@printf "\033[1;31m❌ERASED❌\n"
	rm -f $(NAME)

re: fclean all
