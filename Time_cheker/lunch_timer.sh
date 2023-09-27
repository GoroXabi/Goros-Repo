#!/bin/bash

if [[ $1 -gt 10000 ]]
then
	echo "SIZE TOO LARGE"
else
	if [[ $2 -gt 10000 ]]
	then
	echo "TIMES TOO LARGE"
	else
		gcc -Wall -Wextra -Werror -D SIZE=$1 -D TIMES=$2 libft.a time_checker.c && ./a.out
		rm -f a.out
	fi
fi
