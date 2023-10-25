/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xortega <xortega@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 11:44:25 by xortega           #+#    #+#             */
/*   Updated: 2023/10/25 16:51:58 by xortega          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "SUPERLIBFT/libft.h"
#include "pipex.h"

char	*real_read(int fd)
{
	char	dst[84];

	read(fd, dst, 82);
	dst[82] = '\0';
	return (ft_strdup(dst));
}

int	main(int argc, char *argv[], char **envp)
{
	char	*argv2[3];
	pid_t	pid;
	int		pip[2];
	int		dst_fd;			

	if (argc < 2)
		return (0);
	pipe(pip);
	pid = fork();
	if (pid == 0)
	{
		close(pip[PIPE_READ]);
		dup2(pip[PIPE_WRITE], STDOUT_FILENO);
		close(pip[PIPE_WRITE]);
		argv2[0] = ft_strdup(argv[2]);
		argv2[1] = ft_strdup(argv[1]);
		argv2[2] = NULL;
		//printf("argv2[0]= %s\n", argv2[0]);
		//printf("argv2[1]= %s\n", argv2[1]);
		execve(ft_strjoin("/bin/", argv2[0]), argv2, envp);
	}
	else
	{
		close(pip[PIPE_WRITE]);
		//printf("pipe in: [%s]\n", real_read(pip[PIPE_READ]));
		argv2[0] = ft_strdup(argv[3]);
		argv2[1] = real_read(pip[PIPE_READ]);
		argv2[2] = NULL;
		dst_fd = open(argv[4], O_RDWR, 0777);
		pid = fork();
		if (pid == 0)
		{
			printf("argv2[0] [%s]\n", argv2[0]);
			printf("argv2[1] [%s]\n", argv2[1]);
			dup2(dst_fd, STDOUT_FILENO);
			close(dst_fd);
			execve(ft_strjoin("/usr/bin/", argv2[0]), argv2, envp);
		}
	}
	return (0);
}
