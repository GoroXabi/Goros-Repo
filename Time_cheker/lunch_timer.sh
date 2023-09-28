#!/bin/bash

if [[ $1 -gt 10000 ]]
then
	echo "SIZE TOO LARGE"
else
	if [[ $2 -gt 10000 ]]
	then
	echo "TIMES TOO LARGE"
	else
		if [[ $3 = "split" ]]
		then
			gcc -Wall -Wextra -Werror -D SIZE=$1 -D TIMES=$2 -D FUNCTION=1 time_checker.c libft.a && ./a.out
			rm -f a.out
		elif [[ $3 = "printf" ]]
		then
			gcc -Wall -Wextra -Werror -D SIZE=$1 -D TIMES=$2 -D FUNCTION=2 time_checker.c libft.a && ./a.out
			rm -f a.out
		elif [[ $3 = "gnl" ]]
		then
			gcc -Wall -Wextra -Werror -D SIZE=$1 -D TIMES=$2 -D FUNCTION=3 time_checker.c libft.a && ./a.out
			rm -f a.out
		elif [[ $3 = "all" ]]
		then
			gcc -Wall -Wextra -Werror -D SIZE=$1 -D TIMES=$2 -D FUNCTION=0 time_checker.c libft.a && ./a.out
			rm -f a.out
		else
			gcc -Wall -Wextra -Werror -D SIZE=$1 -D TIMES=$2 -D FUNCTION=4 time_checker.c libft.a && ./a.out
			rm -f a.out
		fi
	fi
fi
