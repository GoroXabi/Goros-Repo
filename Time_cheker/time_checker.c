/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_checker.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xortega <xortega@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 16:05:49 by xortega           #+#    #+#             */
/*   Updated: 2023/09/27 17:27:18 by xortega          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"
#include<time.h>
#include<stdio.h>
#include<stdlib.h>

#ifndef SIZE
# define SIZE 100
#endif

#ifndef TIMES
# define TIMES 100
#endif

#ifndef FUNCTION
# define FUNCTION 4
#endif

//int argc, char const *argv[]
char	*rand_str(char **random_str, int size)
{
	int		count;
	int		random_size;
	char	random_char;

	srand(time(NULL) + rand());
	count = 0;
	random_size = rand() % size;
	random_str[0] = malloc(sizeof(char) * random_size);
	while (random_size > count)
	{
		random_char = (rand() % (122 - 32) + 32);
		random_str[0][count] = random_char;
		count++;
	}
	random_str[0][random_size] = '\0';
	return (random_str[0]);
}

char	rand_char(void)
{
	srand(time(NULL) + rand());
	return (rand() % (122 - 32) + 32);
}

int		rand_int(void)
{
	srand(time(NULL) + rand());
	return (rand() % SIZE);
}	

int	main(void)
{
	clock_t	begin;
	clock_t	end;
	char	c;
	char	*temp;
	int		n;
	double	time_spent = 0.0;

	if (FUNCTION == 4)
	{
		printf("Please intput in the third argument the function to test:\nsplit\nprintf\ngnl\nall\n");
		return (0);
	}
	if (FUNCTION == 1 || FUNCTION == 0)
	{
		for (int i = 0; i < TIMES; i++)
		{
			temp = rand_str(&temp, SIZE);
			c = rand_char();
			begin = clock();
			ft_split(temp, c);
			end = clock();
	//		printf("ran |dom char %c; number %d: %s\n", c, i, temp);
			free(temp);
			temp = NULL;
			time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
		}
	}
	if (FUNCTION == 2 || FUNCTION == 0)
	{
		for (int i = 0; i < TIMES; i++)
		{
			temp = rand_str(&temp, SIZE);
			c = rand_char();
			n = rand_int();
			begin = clock();
			printf("random number: %d\n", n);
			printf("random hexadecimal number: %X\n", n);
			printf("random string: %s\n", temp);
			printf("random char: %c\n", c);
			end = clock();
			free(temp);
			temp = NULL;
			time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
		}	
	}
	printf("SECS: %lf\n", time_spent);
//	system("leaks a.out");
	return (0);
}

