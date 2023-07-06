/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xortega <xortega@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 10:15:18 by xortega           #+#    #+#             */
/*   Updated: 2023/07/06 14:43:13 by xortega          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	gnl_strlen(const char *str)
{
	int	c;

	if (!str)
		return (0);
	c = 0;
	while (str[c])
		c++;
	return (c);
}

void	gnl_cpy(char *src, char **dst, int start)
{
	int		k;

	k = 0;
	while (src[k] != '\0')
	{
		dst[0][start] = src[k];
		start++;
		k++;
	}
	dst[0][start] = '\0';
}

void	gnl_forget(t_struct *all)
{
	if (!all->temp)
	{
		free(all->rest);
		all->rest = NULL;
	}
	else
	{
		free(all->temp);
		all->temp = NULL;
	}
	free(all->buff);
	all->buff = NULL;
}

int	gnl_search(t_struct *all)
{
	int	k;

	if (!all->temp || all->temp[0] == '\0')
		return (-1);
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

char	*gnl_shorter(t_struct *all, int sh)
{
	char	*dst;
	int		k;

	if (all->rd < 0)
		return (gnl_forget(all), NULL);
	if (sh >= 0)
	{
		gnl_cut(all, sh);
		dst = gnl_pack(all, sh);
		return (gnl_forget(all), dst);
	}
	else
	{
		if (!all->temp || all->temp[0] == '\0')
			return (gnl_forget(all), NULL);
		k = -1;
		dst = malloc(sizeof(char) * (gnl_strlen(all->temp) + 1));
		if (!dst)
			return (gnl_forget(all), NULL);
		while (all->temp[++k])
			dst[k] = all->temp[k];
		dst[k] = '\0';
		return (gnl_forget(all), dst);
	}
	return (gnl_forget(all), dst);
}
