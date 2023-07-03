/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xortega <xortega@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 10:15:18 by xortega           #+#    #+#             */
/*   Updated: 2023/05/30 15:59:54 by xortega          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_list	*ft_lstnew(int fd)
//crea un nuevo nodo
{
	t_list	*node;

	node = (t_list *)malloc(sizeof(t_list));
	if (!node)
		return (NULL);
	node -> buff = NULL;
	node -> file_descriptor = fd;
	node -> count = 0;
	node -> next = NULL;
	return (node);
}

void	ft_lstadd_back(t_list *node, t_list	*new)
//pon un nodo delante de una lista
{
//	printf("mecagoentuputamadre\n");
	while (node->next != NULL)
	{
		if (node->next == NULL)
			node->next = new;
		node = node->next;
	}
}

t_list	*get_node(t_list *node, int fd)
//encuentra el nodo, si no crealo
{
	if (!node)
	{
		node = ft_lstnew(fd);
		return (node);
	}
	if (node->file_descriptor == fd)
		return (node);
	while (node->next != NULL)
	{
		if (node->file_descriptor == fd)
			return (node);
		node = node->next;
	}
	ft_lstadd_back(node, ft_lstnew(fd));
	return (node);
}

char	*sub(char *buff, int start, int final)
//substr simple
{
	char	*dst;
	int		k;

	k = 0;
	dst = malloc(sizeof(char) * (final - start + 1));
	if (!dst)
		return (NULL);
	while (start <= final)
	{
		dst[k] = buff[start];
		start++;
		k++;
	}
	dst[k] = '\0';
	return (dst);
}
