#!/bin/bash

if [[ $# -eq 0  ]]
then
	gcc -Wall -Wextra -Werror libft.a time_checker.c && ./a.out
	rm -f a.out
elif [[ $2 -gt 10000 ]]
then
	echo "SIZE TOO LARGE"
elif [[ $3 -gt 10000 ]]
then
	echo "TIMES TOO LARGE"
elif [[ $1 = "split" ]]
then
	gcc -Wall -Wextra -Werror -D SIZE=$2 -D TIMES=$3 -D FUNCTION=1 libft.a time_checker.c && ./a.out
	rm -f a.out
elif [[ $1 = "printf" ]]
then
	gcc -Wall -Wextra -Werror -D SIZE=$2 -D TIMES=$3 -D FUNCTION=2 libft.a time_checker.c && ./a.out
	rm -f a.out
elif [[ $1 = "gnl" ]]
then
	gcc -Wall -Wextra -Werror -D SIZE=$2 -D TIMES=$3 -D FUNCTION=3 libft.a time_checker.c && ./a.out
	rm -f a.out
elif [[ $1 = "all" ]]
then
	gcc -Wall -Wextra -Werror -D SIZE=$2 -D TIMES=$3 -D FUNCTION=0 libft.a time_checker.c && ./a.out
	rm -f a.out
else
	gcc -Wall -Wextra -Werror -D SIZE=$2 -D TIMES=$3 -D FUNCTION=4 libft.a time_checker.c && ./a.out
	rm -f a.out
fi
