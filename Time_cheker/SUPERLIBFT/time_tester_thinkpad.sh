#!/bin/bash

size=100
times=100

if [[ $# -eq 2 ]]
then
	size=$2
fi
if [[ $# -eq 3 ]]
then
	size=$2
	times=$3
fi
if [[ $# -eq 0  ]]
then
	make
	gcc -Wall -Wextra -Werror -DSIZE=$size -DTIMES=$times -DFUNCTION=0 time_tester.c libft.a && ./a.out
	rm -f a.out
elif [[ $1 = "-h" ]]
then
	echo "The first argument indicates the funcion to test ("all" to test all)"
	echo "The second argument indicates the Size of the strings used to test"
	echo "The third argument indicates the number of Times that yout funcion whill be called"
elif [[ $1 = "split" ]]
then
	if [[ $size -gt 100000 ]]
	then
	echo "SIZE TOO LARGE"
	echo "you can change this cap in the .sh"
	elif [[ $times -gt 100000 ]]
	then
	echo "TIMES TOO LARGE" 
	echo "you can change this cap in the .sh"
	else
	make
	gcc -Wall -Wextra -Werror -DSIZE=$size -DTIMES=$times -DFUNCTION=1 time_tester.c libft.a && ./a.out
	rm -f a.out
	fi
elif [[ $1 = "printf" ]]
then
	if [[ $size -gt 10000 ]]
	then
	echo "SIZE TOO LARGE"
	echo "you can change this cap in the .sh"
	elif [[ $times -gt 100000 ]]
	then
	echo "TIMES TOO LARGE"
	echo "you can change this cap in the .sh"
	else
	make
	gcc -Wall -Wextra -Werror -DSIZE=$size -DTIMES=$times -DFUNCTION=2 time_tester.c libft.a && ./a.out
	rm -f a.out
	fi
elif [[ $1 = "gnl" ]]
then
	if [[ $size -gt 10000 ]]
	then
	echo "SIZE TOO LARGE"
	echo "you can change this cap in the .sh"
	elif [[ $times -gt 10000 ]]
	then
	echo "TIMES TOO LARGE"
	echo "you can change this cap in the .sh"
	else
	make
	gcc -Wall -Wextra -Werror -DSIZE=$size -DTIMES=$times -DFUNCTION=3 time_tester.c libft.a && ./a.out
	rm -f a.out
	fi
elif [[ $1 = "all" ]]
then
	if [[ $size -gt 10000 ]]
	then
	echo "SIZE TOO LARGE"
	echo "you can change this cap in the .sh"
	elif [[ $times -gt 10000 ]]
	then
	echo "TIMES TOO LARGE"
	echo "you can change this cap in the .sh"
	else
	make
	gcc -Wall -Wextra -Werror -DSIZE=$size -DTIMES=$times -DFUNCTION=0 time_tester.c libft.a && ./a.out
#	rm -f a.out
	fi
else
	echo "$1 is not in the test, -h for more help"
fi
make fclean
