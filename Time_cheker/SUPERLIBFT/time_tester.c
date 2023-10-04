/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_checker.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xortega <xortega@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 16:05:49 by xortega           #+#    #+#             */
/*   Updated: 2023/09/29 16:57:11 by xortega          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"
#include<time.h>
#include<stdio.h>
#include<stdlib.h>

/*#ifndef SIZE
# define SIZE 100
#endif

#ifndef TIMES
# define TIMES 100
#endif

#ifndef FUNCTION
# define FUNCTION 4
#endif*/

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

int	rand_int(void)
{
	srand(time(NULL) + rand());
	return (rand() % SIZE);
}	

int	main(void)
{
	clock_t	begin;
	clock_t	end;
	int		stdout;
	int		fd;
	char	c;
	char	*temp;
	int		n = 0;
	double	time_spent = 0.0;
	double	total_time = 0.0;

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
			time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
		}
		printf("SPLIT TOOK: %lf SECS\n", time_spent);
		if (FUNCTION == 1)
			return (0);
		total_time += time_spent;
		time_spent = 0.0;
	}
	if (FUNCTION == 2 || FUNCTION == 0)
	{
		fd = open("/dev/null", O_WRONLY);
		if (fd < 0)
			return (1);
		dup2(1, fd);
		close(1);
		for (int i = 0; i < (TIMES); i++)
		{
			temp = rand_str(&temp, SIZE);
			c = rand_char();
			n = rand_int();
			begin = clock();
			ft_printf("%d", n);
			ft_printf("%X", n);
			ft_printf("%s", temp);
			ft_printf("%c", c);
			end = clock();
			free(temp);
			time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
		}
		dup2(fd, 1);
		close(fd);
		printf("PRINTF TOOK: %lf SECS\n", time_spent);
		if (FUNCTION == 2)
			return (0);
		total_time += time_spent;
		time_spent = 0.0;
	}
	if (FUNCTION == 3 || FUNCTION == 0)
	{
		stdout = dup(1);
		remove("GNL_TEXT.txt");
		fd = open("GNL_TEXT.txt", O_RDWR | O_CREAT, 0777);
		if (fd < 0)
			return (0);
		for (int i = 0; i < (TIMES); i++)
		{
			temp = rand_str(&temp, SIZE);
			ft_putstr_fd(temp, fd);
			free(temp);
			ft_putstr_fd("\n", fd);
		}
		dup2(stdout, 1);
		close(fd);
		fd = open("GNL_TEXT.txt", O_RDWR, 0777);
		begin = clock();
		while ((get_next_line(fd)))
			;
		end = clock();
		time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
		printf("GNL TOOK: %lf SECS\n", time_spent);
		if (FUNCTION == 3)
			return (0);
		total_time += time_spent;
		time_spent = 0.0;
	}
	remove("GNL_TEXT.txt");
	printf("ALL THE TESTS TOOK: %lf SECS\n", total_time);
//	system("leaks a.out");
	return (0);
}

