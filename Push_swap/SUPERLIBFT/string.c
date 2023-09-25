/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xortega <xortega@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 10:05:07 by xortega           #+#    #+#             */
/*   Updated: 2023/07/06 10:11:59 by xortega          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	print_string(va_list lst)
{
	char	*string;

	string = va_arg(lst, char *);
	if (!string)
	{
		write(1, "(null)", 6);
		return (6);
	}
	return (write(1, string, ft_strlen(string)));
}
