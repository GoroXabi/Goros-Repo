# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: xortega <xortega@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/25 12:09:10 by xortega           #+#    #+#              #
#    Updated: 2023/07/17 12:52:23 by xortega          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME := SUPERlibft.a
SOURCES :=	ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c ft_isprint.c \
			ft_strchr.c ft_strdup.c ft_strjoin.c ft_strlcat.c ft_strlcpy.c \
			ft_strlen.c ft_strncmp.c ft_strnstr.c ft_strrchr.c ft_memchr.c \
			ft_memcmp.c ft_memcpy.c ft_memset.c ft_memmove.c ft_bzero.c \
			ft_toupper.c ft_tolower.c ft_atoi.c ft_calloc.c ft_substr.c \
			ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c ft_striteri.c \
			ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
			ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c \
			ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c \
			ft_printf.c address.c char.c decimal.c \
			hexadecimal.c string.c unsigned.c \
			get_next_line.c get_next_line_utils.c

OBJS		:= $(SOURCES:.c=.o)
CC				:= gcc
CFLAGS			:= -Wall -Wextra -Werror
AR				:= ar -r

.SILENT:

all: $(NAME)

$(NAME): patatas $(OBJS)
	@printf "\rCompilated! ..................................................\n\n"
	@printf "\033[1;97m|----------------------------------------------------------------|\n"
	$(AR) $(NAME) *.o 2>/dev/null || true

patatas:
	@clear
	@printf "\
\033[1;97m|----------------------------------------------------------------|\n\n\
\033[0;95m   _____ __  ______  __________ \033[0;31m    __    ________  ____________\n\
\033[0;95m  / ___// / / / __ \/ ____/ __ \ \033[0;33m  / /   /  _/ __ )/ ____/_  __/\n\
\033[0;95m  \__ \/ / / / /_/ / __/ / /_/ /\033[0;32m  / /    / // __  / /_    / /   \n\
\033[0;95m ___/ / /_/ / ____/ /___/ _, _/ \033[1;35m / /____/ // /_/ / __/   / /    \n\
\033[0;95m/____/\____/_/   /_____/_/ |_|  \033[0;34m/_____/___/_____/_/     /_/     \n"
	@printf "\033[0;33mCompiling \033[0;32m"

%.o: %.c
	@printf "\033[0;33m.\033[0;32m"
	$(CC) -c $(CFLAGS) $?

clean:
	@rm -f *.o

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re LIB_OBJS GNL_OBJS PRINT_OBJS