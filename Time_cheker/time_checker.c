/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_checker.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xortega <xortega@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 16:05:49 by xortega           #+#    #+#             */
/*   Updated: 2023/09/26 17:20:38 by xortega          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"
#include<time.h>
#include<stdio.h>
#include<stdlib.h>

//int argc, char const *argv[]
char	*rand_str(void)
{
	int		count;
	int		random_size;
	char	*random_str;
	char	random_char;

	srand(time(NULL) + rand());
	count = 0;
	random_size = rand() % 100;
	random_str = malloc(sizeof(char) * random_size);
	while (random_size > count)
	{
		random_char = (rand() % (122 - 32) + 32);
		random_str[count] = random_char;
		count++;
	}
	random_str[random_size] = '\0';
	return (random_str);
}

char	rand_char(void)
{
	srand(time(NULL) + rand());
	return (rand() % (122 - 32) + 32);
}

int	main(void)
{
	clock_t	begin;
	clock_t	end;
	char	*temp;
	double	time_spent = 0.0;

	for (int i = 0; i < 100; i++)
	{
		begin = clock();
		temp = rand_str();
		ft_split(temp, rand_char());
		free(temp);
		temp = NULL;
		end = clock();
		time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
	}
	printf("SECS: %lf\n", time_spent);
	return (0);
}
