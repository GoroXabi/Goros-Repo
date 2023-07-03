/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xortega <xortega@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 09:59:28 by xortega           #+#    #+#             */
/*   Updated: 2023/06/13 10:57:47 by xortega          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "get_next_line_utils.c"

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 555
#endif

int	search(t_list *node, int start)
{
	if (!node->buff)
		return (0);
	if (start > 0)
		start++;
	while (node->buff && node->buff[start] != '\0')
	{
		if (node->buff[start] == '\n')
		{
			node->count = start + 1;
			return (1);
		}
		start++;
	}
	return (0);
}

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

void	fill(char *temp2, t_list *node, int lenofbuff, int buffsize)
{
	char	*newbuff;
	int		count1;
	int		count2;

	count1 = 0;
	count2 = 0;
	newbuff = malloc (sizeof(char) * (lenofbuff + buffsize));
	while (--lenofbuff >= 0)
	{
		newbuff[count1] = node->buff[count1];
		count1++;
	}
	while (--buffsize >= 0)
	{
		newbuff[count1] = temp2[count2];
		count1++;
		count2++;
	}
	if (node->buff)
		free(node->buff);
	node->buff = newbuff;
	newbuff = NULL;
	free(newbuff);
}

int	getbuff(t_list *node)
{
	char	*temp;
	int		lenofbuff;
	int		rd;

	lenofbuff = ft_strlen(node->buff);
	temp = malloc (sizeof(char) * (BUFFER_SIZE + 1));
	rd = read(node->file_descriptor, temp, BUFFER_SIZE);
	temp[BUFFER_SIZE] = '\0';
	fill(temp, node, lenofbuff, BUFFER_SIZE);
	temp = NULL;
	free(temp);
	return (rd);
}

char	*get_next_line(int fd)
{
	static t_list	*head;
	t_list			*current_node;
	int				count;

	if (fd < 0)
		return (NULL);
	head = get_node(head, fd);
	current_node = head;
	getbuff(current_node);
	count = 0;
	while (count > -1)
	{
		count = current_node->count;
		if (search(current_node, count) == 0)
			return (NULL);
		else
			return (sub(current_node->buff, count, (current_node->count - 1)));
	}
	return (NULL);
}

int	main(void)
{
	int	fd;
	int	fd2;

	fd = open("../test.txt", O_RDONLY);
	fd2 = open("../test2.txt", O_RDONLY);
//	while (get_next_line(fd) != NULL)
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd2));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd2));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd2));
//	printf("%sBREAK\n", get_next_line(fd2));
	close(fd);
	close(fd2);
}
