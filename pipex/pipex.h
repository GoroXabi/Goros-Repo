/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xortega <xortega@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 13:57:40 by xortega           #+#    #+#             */
/*   Updated: 2023/11/10 12:18:35 by xortega          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <fcntl.h>
# include <errno.h>	

# define PIPE_READ 0
# define PIPE_WRITE 1

typedef struct pipex_struct
{
	int		pip[2];
	pid_t	pid;
	int		dst_fd;
	int		src_fd;
	pid_t	error;
	int		argc;
}					t_pipex;

#endif