#!/bin/bash

make re;

if [[ $# -eq 0  ]]
then
	gcc -Wall -Wextra -Werror libft.a time_tester.c && ./a.out
	rm -f a.out
elif [[ $1 = "split" ]]
then
	if [[ $2 -gt 100000 ]]
	then
	echo "SIZE TOO LARGE"
	echo "you can change this cap in the .sh"
	elif [[ $3 -gt 100000 ]]
	then
	echo "TIMES TOO LARGE" 
	echo "you can change this cap in the .sh"
	else
	gcc -Wall -Wextra -Werror -D SIZE=$2 -D TIMES=$3 -D FUNCTION=1 libft.a time_tester.c && ./a.out
	rm -f a.out
	fi
elif [[ $1 = "printf" ]]
then
	if [[ $2 -gt 10000 ]]
	then
	echo "SIZE TOO LARGE"
	echo "you can change this cap in the .sh"
	elif [[ $3 -gt 100000 ]]
	then
	echo "TIMES TOO LARGE"
	echo "you can change this cap in the .sh"
	else
	gcc -Wall -Wextra -Werror -D SIZE=$2 -D TIMES=$3 -D FUNCTION=2 libft.a time_tester.c && ./a.out
	rm -f a.out
	fi
elif [[ $1 = "gnl" ]]
then
	if [[ $2 -gt 10000 ]]
	then
	echo "SIZE TOO LARGE"
	echo "you can change this cap in the .sh"
	elif [[ $3 -gt 10000 ]]
	then
	echo "TIMES TOO LARGE"
	echo "you can change this cap in the .sh"
	else
	gcc -Wall -Wextra -Werror -D SIZE=$2 -D TIMES=$3 -D FUNCTION=3 libft.a time_tester.c && ./a.out
	rm -f a.out
	fi
elif [[ $1 = "all" ]]
then
	if [[ $2 -gt 10000 ]]
	then
	echo "SIZE TOO LARGE"
	echo "you can change this cap in the .sh"
	elif [[ $3 -gt 10000 ]]
	then
	echo "TIMES TOO LARGE"
	echo "you can change this cap in the .sh"
	else
	gcc -Wall -Wextra -Werror -D SIZE=$2 -D TIMES=$3 -D FUNCTION=0 libft.a time_tester.c && ./a.out
	rm -f a.out
	fi
else
	gcc -Wall -Wextra -Werror -D SIZE=$2 -D TIMES=$3 -D FUNCTION=4 libft.a time_tester.c && ./a.out
	rm -f a.out
fi
make fclean