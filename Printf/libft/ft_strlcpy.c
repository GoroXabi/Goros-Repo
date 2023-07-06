/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xortega <xortega@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 15:16:50 by xortega           #+#    #+#             */
/*   Updated: 2023/05/15 11:10:44 by xortega          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = -1;
	while (src[i] != '\0')
		i++;
	if (dstsize == 0)
		return (i);
	while (++j < (dstsize - 1) && src[j] != '\0')
		dst[j] = src[j];
	dst[j] = '\0';
	return (i);
}
