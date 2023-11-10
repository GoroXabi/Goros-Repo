/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aaaa.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xortega <xortega@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 13:23:23 by xortega           #+#    #+#             */
/*   Updated: 2023/11/10 12:18:37 by xortega          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include "pipex.h"

void	ford(t_pipex *a)
{
	pid_t	i;
	pid_t	o;

	i = fork();
	if (i == 0)
	{
		printf("im the child\n");
		exit(2);
	}
	else
	{
		o = waitpid(i, NULL, WIFEXITED(a->error));
		printf("im the parent\n");
		printf("child pid is : %d\n", i);
		printf("the return of waitpid is: %d\n", o);
		printf("a has: %d\n", a->error);
	}
}

int	main(void)
{
	t_pipex	a;

	ford(&a);
	return (0);
}
