/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a.c                                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xortega <xortega@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 11:51:27 by xortega           #+#    #+#             */
/*   Updated: 2023/06/13 11:55:36 by xortega          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

int	main(void)
{
	int		fd;
	char	*dst;

	dst = malloc(sizeof(char) * 6);
	fd = open("../test2.txt", O_RDONLY);
	read(fd, dst, 5);
	dst[5] = '\0';
	printf("%s", dst);
	read(fd, dst, 5);
	dst[5] = '\0';
	printf("%s", dst);
	return (0);
}
