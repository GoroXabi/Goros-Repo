# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: xortega <xortega@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/25 12:09:10 by xortega           #+#    #+#              #
#    Updated: 2023/10/31 10:25:13 by xortega          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME := pipex
SOURCES :=	pipex.c
CC				:= gcc
CFLAGS			:= -Wall -Wextra -Werror

.SILENT:

all: $(NAME)

$(NAME):
	$(CC) $(CFLAGS) pipex.c ./SUPERLIBFT/SUPERlibft.a -o $(NAME)
	chmod 777 $(NAME)

fclean:
	@printf "\033[1;31m❌ERASED❌\n"
	rm -f $(NAME)

re: fclean all
