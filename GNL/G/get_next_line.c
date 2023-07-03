/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xortega <xortega@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 09:59:28 by xortega           #+#    #+#             */
/*   Updated: 2023/06/15 11:04:56 by xortega          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 7
#endif

int	ft_strlen(const char *str)
{
	int	c;

	if (!str)
		return (0);
	c = 0;
	while (str[c])
		c++;
	return (c);
}

void	cpy(char *dst, char *src, int s)
{
	int	k;

	k = 0;
	while (src[k])
	{
		dst[s] = src[k];
		k++;
		s++;
	}
}

char	*merge(char *first, char *second)
{
	char	*dst;
	int		first_len;
	int		second_len;
	int		k;

	if (!first && !second)
		return (NULL);
	first_len = ft_strlen(first);
	second_len = ft_strlen(second);
	k = -1;
	dst = malloc(sizeof(char) * (first_len + second_len));
	if (first_len > 0)
		cpy(dst, first, 0);
	if (second_len > 0)
		cpy(dst, second, first_len);
	return (dst);
}

int	search(char *temp)
{
	int	k;

	if (!temp)
		return (-1);
	k = -1;
	while (temp[++k])
		if (temp[k] == '\n' || temp[k] == '\0')
			return (++k);
	return (-1);
}

char	*cut(char *all, int nl)
{
	char	*dst;
	int		k;

	dst = NULL;
	k = 0;
	if ((ft_strlen(all) - nl) <= 0 || !all)
		return (NULL);
	dst = malloc (sizeof(char) * (ft_strlen(all) - nl));
	while (all[nl] && all)
	{
		dst[k] = all[nl];
		k++;
		nl++;
	}
	return (dst);
}

char	*pack(char *all, int nl)
{
	char	*dst;
	int		k;

	dst = NULL;
	k = 0;
	dst = malloc (sizeof(char) * nl);
	while (k < nl)
	{
		dst[k] = all[k];
		k++;
	}
	return (dst);
}

void	del(char *temp, char *all, char *reminder, char *dst)
{
	if (dst)
	{
		dst = NULL;
		free(dst);
	}
	if (temp)
	{
		temp = NULL;
		free(temp);
	}
	if (all)
	{
		all = NULL;
		free(all);
	}
	if (!reminder)
		free(reminder);
}

char	*get_next_line(int fd)
{
	static char	*reminder;
	char		*temp;
	char		*all;
	char		*dst;
	int			nl;

	temp = malloc(sizeof(char) * BUFFER_SIZE);
	read(fd, temp, BUFFER_SIZE);
	if (!reminder && temp[0] == '\0')
		return (NULL);
	all = merge(reminder, temp);
//	printf("--DEBERIA DE ESTAR VACIO:\nREMINDER: %s, TEMP: %s--\n", reminder, temp);
	nl = search(all);
	while (nl <= 0)
	{
		temp = malloc(sizeof(char) * BUFFER_SIZE);
		read(fd, temp, BUFFER_SIZE);
		dst = merge(all, temp);
		cpy(all, dst, 0);
		del(temp, "", reminder, "");
	//	printf("--DEBERIA DE ESTAR VACIO:\nALL: %s, TEMP: %s--\n", all, temp);
		nl = search(all);
	}
	reminder = cut(all, nl);
	dst = pack(all, nl);
	del(temp, all, reminder, "");
	return (dst);
}

int	main(void)
{
	int	fd;

	fd = open("../test.txt", O_RDONLY);
  	printf("OUT: %s", get_next_line(fd));
	printf("----\n");
	printf("OUT: %s", get_next_line(fd));
	printf("----\n");
	printf("OUT: %s", get_next_line(fd));
	printf("----\n");
	printf("OUT: %s", get_next_line(fd));
	printf("----\n");
	printf("OUT: %s", get_next_line(fd));
	printf("----\n");
	printf("OUT: %s", get_next_line(fd));
	printf("----\n");
	printf("OUT: %s", get_next_line(fd));
	printf("----\n");
	printf("OUT: %s", get_next_line(fd));
	printf("----\n");
	printf("OUT: %s", get_next_line(fd));
	printf("----\n");
	printf("OUT: %s", get_next_line(fd));
	printf("----\n");
	printf("OUT: %s", get_next_line(fd));
	printf("----\n");
	printf("OUT: %s", get_next_line(fd));
	printf("----\n");
	printf("OUT: %s", get_next_line(fd));
	printf("----\n");
	printf("OUT: %s", get_next_line(fd));
	printf("----\n");
	printf("OUT: %s", get_next_line(fd));
	printf("----\n");
	printf("OUT: %s", get_next_line(fd));
	printf("----\n");
	printf("OUT: %s", get_next_line(fd));
	close(fd);
}
