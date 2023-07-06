/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xortega <xortega@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 11:53:35 by xortega           #+#    #+#             */
/*   Updated: 2023/07/06 14:43:05 by xortega          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 20
#endif

void	gnl_addnew(t_struct *all, int fd)
{
	char	*after;
	int		before_len;

	before_len = gnl_strlen(all->temp);
	after = malloc(sizeof(char) * (before_len + BUFFER_SIZE + 1));
	if (!after)
	{
		free(all->temp);
		all->temp = NULL;
		all->rd = -1;
		return ;
	}
	all->rd = read(fd, all->buff, BUFFER_SIZE);
	if (all->rd == -1)
		return ;
	all->buff[all->rd] = '\0';
	gnl_cpy(all->temp, &after, 0);
	gnl_cpy(all->buff, &after, before_len);
	free(all->temp);
	all->temp = NULL;
	all->temp = after;
}

void	gnl_remember(t_struct *all, int fd)
{
	int	k;
	int	rest_len;

	k = 0;
	rest_len = gnl_strlen(all->rest);
	all->temp = malloc(sizeof(char) * (rest_len + BUFFER_SIZE + 1));
	if (!all->temp)
		return ;
	all->rd = read(fd, all->buff, BUFFER_SIZE);
	if (all->rd == -1)
	{
		free(all->temp);
		all->temp = NULL;
		return ;
	}
	all->buff[all->rd] = '\0';
	gnl_cpy(all->rest, &all->temp, 0);
	gnl_cpy(all->buff, &all->temp, rest_len);
	free(all->rest);
	all->rest = NULL;
}

void	gnl_cut(t_struct *all, int sh)
{
	int		k;

	k = 0;
	all->rest = malloc (sizeof(char) * (gnl_strlen(all->temp) - sh + 1));
	if (!all->rest)
		return ;
	while (all->temp[sh])
	{
		all->rest[k] = all->temp[sh];
		k++;
		sh++;
	}
	all->rest[k] = '\0';
}

char	*gnl_pack(t_struct *all, int sh)
{
	char	*dst;
	int		k;

	k = 0;
	dst = malloc (sizeof(char) * (sh + 1));
	if (!dst)
	{
		free(all->temp);
		all->temp = NULL;
		return (NULL);
	}
	while (k < sh)
	{
		dst[k] = all->temp[k];
		k++;
	}
	dst[k] = '\0';
	return (dst);
}

char	*get_next_line(int fd)
{
	static t_struct	all = {NULL, NULL, NULL, 1};
	int				sh;

	if (fd < 0)
		return (NULL);
	if (all.rest == NULL)
	{
		all.rest = malloc(sizeof(char) * 1);
		if (!all.rest)
			return (gnl_forget(&all), NULL);
		all.rest[0] = '\0';
	}
	all.buff = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!all.buff)
		return (gnl_forget(&all), NULL);
	gnl_remember(&all, fd);
	sh = gnl_search(&all);
	while (all.rd > 0 && sh <= 0 && all.temp)
	{
		gnl_addnew(&all, fd);
		if (all.temp && all.rd >= 0)
			sh = gnl_search(&all);
	}
	return (gnl_shorter(&all, sh));
}
