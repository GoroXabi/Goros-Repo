#!/bin/bash

if [[ $# -eq 0  ]]
then
	make re;
	gcc -Wall -Wextra -Werror -D SIZE=100 -D TIMES=100 -D FUNCTION=0 time_tester.c libft.a && ./a.out
	rm -f a.out
elif [[ $1 = "-h" ]]
then
	echo "The first argument indicates the funcion to test ("all" to test all)"
	echo "The second argument indicates the Size of the strings used to test"
	echo "The third argument indicates the number of Times that yout funcion whill be called"
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
	make re;
	gcc -Wall -Wextra -Werror -D SIZE=$2 -D TIMES=$3 -D FUNCTION=1 time_tester.c libft.a && ./a.out
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
	make re;
	gcc -Wall -Wextra -Werror -D SIZE=$2 -D TIMES=$3 -D FUNCTION=2 time_tester.c libft.a && ./a.out
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
	make re;
	gcc -Wall -Wextra -Werror -D SIZE=$2 -D TIMES=$3 -D FUNCTION=3 time_tester.c libft.a && ./a.out
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
	make re;
	gcc -Wall -Wextra -Werror -D SIZE=$2 -D TIMES=$3 -D FUNCTION=0 time_tester.c libft.a && ./a.out
	rm -f a.out
	fi
else
	echo "$1 is not in the test, -h for more help"
fi
make fclean
