/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xortega <xortega@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 16:03:07 by xortega           #+#    #+#             */
/*   Updated: 2023/07/17 10:06:24 by xortega          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>

typedef struct s_struct
{
	char			*buff;
	char			*temp;
	char			*rest[4096];
	int				rd;
}					t_struct;

char	*get_next_line(int fd);
void	addnew(t_struct *all, int fd);
void	remember(t_struct *all, int fd);
void	cut(t_struct *all, int sh, int fd);
char	*pack(t_struct *all, int sh);
int		gnl_strlen(const char *str);
void	cpy(char *src, char **dst, int start);
void	forget(t_struct *all, int fd);
int		search(t_struct *all);
char	*shorter(t_struct *all, int sh, int fd);
#endif
