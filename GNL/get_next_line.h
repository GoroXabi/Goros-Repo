/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xortega <xortega@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 16:03:07 by xortega           #+#    #+#             */
/*   Updated: 2023/06/02 11:12:48 by xortega          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>

typedef struct s_list
{
	char			*buff;
	struct s_list	*next;
	int				file_descriptor;
	int				count;
}					t_list;

char	*get_next_line(int fd);
//int		main(void);
/* utils */
t_list	*ft_lstnew(int fd);
void	ft_lstadd_front(t_list **lst, t_list *new);
t_list	*get_node(t_list *node, int fd);
char	*sub(char *s, int start, int final);
int		ft_strlen(const char *str);
int		search(t_list *node, int start);
void	fill(char *temp2, t_list *node, int lenofbuff, int buffsize);
int		getbuff(t_list *node);
#endif
