# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: xabier <xabier@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/25 12:09:10 by xortega           #+#    #+#              #
#    Updated: 2023/11/03 17:25:46 by xabier           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME := pipex
SOURCES :=	pipex.c
CC				:= gcc
CFLAGS			:= -Wall -Wextra -Werror

.SILENT:

all: $(NAME)

$(NAME):
	$(CC) $(CFLAGS) pipex.c libft.a -o $(NAME)
	chmod 777 $(NAME)

fclean:
	@printf "\033[1;31m❌ERASED❌\n"
	rm -f $(NAME)

re: fclean all
