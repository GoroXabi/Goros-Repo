/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xortega <xortega@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 16:03:07 by xortega           #+#    #+#             */
/*   Updated: 2023/06/30 11:47:34 by xortega          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>

typedef struct s_struct
{
	char			*buff;
	char			*temp;
	char			*rest;
	int				rd;
}					t_struct;

char	*get_next_line(int fd);
void	addnew(t_struct *all, int fd);
void	remember(t_struct *all, int fd);
void	cut(t_struct *all, int sh);
char	*pack(t_struct *all, int sh);
int		gnl_strlen(const char *str);
void	cpy(char *src, char **dst, int start);
void	forget(t_struct *all);
int		search(t_struct *all);
char	*shorter(t_struct *all, int sh);
#endif
