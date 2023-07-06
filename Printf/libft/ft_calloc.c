/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xortega <xortega@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 10:33:57 by xortega           #+#    #+#             */
/*   Updated: 2023/05/15 11:20:38 by xortega          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*str;

	if (count == SIZE_MAX || size == SIZE_MAX)
		return (NULL);
	str = malloc(count * size);
	if (str == NULL)
		return (NULL);
	if (count == 0)
		return (str);
	return (ft_memset(str, '\0', (count * size)));
}
