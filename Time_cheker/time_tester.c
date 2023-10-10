/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_tester.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xortega <xortega@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 16:05:49 by xortega           #+#    #+#             */
/*   Updated: 2023/10/10 13:07:57 by xortega          ###   ########.fr       */
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
void	rand_str(char **random_str, int size)
{
	int		count;
	int		random_size;
	char	random_char;

	srand(time(NULL) + rand());
	count = 0;
	random_size = rand() % size;
	random_str[0] = malloc(sizeof(char) * (random_size + 1));
	while (random_size > count)
	{
		random_char = (rand() % (122 - 32) + 32);
		random_str[0][count] = random_char;
		count++;
	}
	random_str[0][random_size] = '\0';
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
			rand_str(&temp, SIZE);
			c = rand_char();
			begin = clock();
			ft_split(temp, c);
			end = clock();
	//		printf("ran |dom char %c; number %d: %s\n", c, i, temp);
			free(temp);
			temp = NULL;
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
			rand_str(&temp, SIZE);
			c = rand_char();
			n = rand_int();
			begin = clock();
			ft_printf("%d", n);
			ft_printf("%X", n);
			ft_printf("%s", temp);
			ft_printf("%c", c);
			end = clock();
			free(temp);
			temp = NULL;
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
		remove("GNL_TEXT.txt");
		fd = open("GNL_TEXT.txt", O_RDWR | O_CREAT, 0777);
		if (fd < 0)
			return (0);
		for (int i = 0; i < (TIMES); i++)
		{
			rand_str(&temp, SIZE);
			ft_putstr_fd(temp, fd);
			free(temp);
			temp = NULL;
			ft_putstr_fd("\n", fd);
		}
		begin = clock();
		while (TIMES > ++n)
			get_next_line(fd);
		end = clock();
		close(fd);
		time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
		printf("GNL TOOK: %lf SECS\n", time_spent);
		remove("GNL_TEXT.txt");
		if (FUNCTION == 3)
			return (0);
		total_time += time_spent;
		time_spent = 0.0;
	}
	printf("ALL THE TESTS TOOK: %lf SECS\n", total_time);
//	system("leaks a.out");
	return (0);
}

