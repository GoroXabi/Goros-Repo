/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xortega <xortega@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 11:53:35 by xortega           #+#    #+#             */
/*   Updated: 2023/06/29 10:34:31 by xortega          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include "get_next_line.h"

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 42
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

char	*cpy(char *src, char dst, int j)
{
	char	*dst;
	int		k;

	if (!src || src[0] == '\0')
		return (NULL);
	if (dst == NULL)
		dst = malloc(sizeof(char) * ft_strlen(src));
	k = 0;
	while (src[k])
	{
		dst[j] = src[k];
		k++;
		j++;
	}
	dst[j] = '\0';
	return (dst);
}

void	addnew(t_list *all, int fd)
{
	char	*after;
	int		k;
	int		before_len;

	k = 0;
	before_len = ft_strlen(all->temp);
	after = malloc(sizeof(char) * (before_len + BUFFER_SIZE + 1));
	all->rd = read(fd, all->buff, BUFFER_SIZE);
	if (all->rd == -1)
	{
		free(after);
		after = NULL;
		return ;
	}
	all->buff[all->rd] = '\0';
	while (k < before_len)
	{
		after[k] = all->temp[k];
		k++;
	}
	k = 0;
	while (k < BUFFER_SIZE && all->rd > 0)
	{
		after[before_len] = all->buff[k];
		before_len++;
		k++;
	}
	after[before_len] = '\0';
	free(all->temp);
	all->temp = NULL;
	all->temp = after;
}

void	remember(t_list *all, int fd)
{
	int	k;
	int	rest_len;

	k = 0;
	rest_len = ft_strlen(all->rest);
	all->temp = malloc(sizeof(char) * (rest_len + BUFFER_SIZE + 1));
	all->rd = read(fd, all->buff, BUFFER_SIZE);
	if (all->rd == -1)
	{
		free(all->temp);
		all->temp = NULL;
		return ;
	}
	all->buff[all->rd] = '\0';
	while (k < rest_len)
	{
		all->temp[k] = all->rest[k];
		k++;
	}
	k = 0;
	while (k < BUFFER_SIZE && all->rd > 0)
	{
		all->temp[rest_len] = all->buff[k];
		rest_len++;
		k++;
	}
	all->temp[rest_len] = '\0';
	free(all->rest);
	all->rest = NULL;
}

int	search(t_list *all)
{
	int	k;

	if (!all->temp || all->temp[0] == '\0')
		return (-2);
	k = 0;
	while (all->temp[k] != '\0')
	{
		if (all->temp[k] == '\n')
			return (++k);
		k++;
	}
	if (all->rd == 0)
		return (-1);
	return (-2);
}

void	cut(t_list *all, int sh)
{
	int		k;

	k = 0;
	all->rest = malloc (sizeof(char) * (ft_strlen(all->temp) - sh + 1));
	while (all->temp[sh])
	{
		all->rest[k] = all->temp[sh];
		k++;
		sh++;
	}
	all->rest[k] = '\0';
}

char	*pack(t_list *all, int sh)
{
	char	*dst;
	int		k;

	k = 0;
	dst = malloc (sizeof(char) * (sh + 1));
	if (!dst)
		return (NULL);
	while (k < sh)
	{
		dst[k] = all->temp[k];
		k++;
	}
	dst[k] = '\0';
	return (dst);
}

void	forget(t_list *all)
{
	if (!all->temp)
	{
		free(all->rest);
		all->rest = NULL;
	}
	free(all->buff);
	all->buff = NULL;
	free(all->temp);
	all->temp = NULL;
}

char	*get_next_line(int fd)
{
	static t_list	all = {NULL, NULL, NULL, 1};
	char			*dst;
	int				sh;

	if (fd < 0)
		return (NULL);
	if (all.rest == NULL)
	{
		all.rest = malloc(sizeof(char) * 1);
		all.rest[0] = '\0';
	}
	all.buff = malloc(sizeof(char) * BUFFER_SIZE + 1);
	remember(&all, fd);
	sh = search(&all);
	while (all.rd > 0 && sh <= 0)
	{
		if (all.rd > 0)
			addnew(&all, fd);
		sh = search(&all);
	}
	if (all.rd < 0)
	{
		forget(&all);
		return (NULL);
	}
	if (sh >= 0)
	{
		cut(&all, sh);
		dst = pack(&all, sh);
		forget(&all);
		return (dst);
	}
	else
	{
		dst = cpy(all.temp);
		forget(&all);
		return (dst);
	}
}
/*
** 
** int	main(void)
** {
** 	int		fd;
** 	char	*dst;
** 
** 	fd = open("../test2.txt", O_RDONLY);
** 	dst = get_next_line(fd);
** 	printf("%s", dst);
** 	free(dst);
** 	dst = get_next_line(fd);
** 	printf("%s", dst);
** 	free(dst);
** 	dst = get_next_line(fd);
** 	printf("%s", dst);
** 	free(dst);
** 	dst = get_next_line(fd);
** 	printf("%s", dst);
** 	free(dst);
** 	dst = get_next_line(fd);
** 	printf("%s", dst);
** 	free(dst);
** 	dst = get_next_line(fd);
** 	printf("%s", dst);
** 	free(dst);
** 	dst = get_next_line(fd);
** 	printf("%s", dst);
** 	free(dst);
** }
** 
*/