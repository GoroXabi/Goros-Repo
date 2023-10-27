/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xortega <xortega@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 11:44:25 by xortega           #+#    #+#             */
/*   Updated: 2023/10/27 14:23:26 by xortega          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "SUPERLIBFT/libft.h"
#include "pipex.h"
#include <unistd.h>

char	*real_read(int fd)
{
	char	dst[84];

	read(fd, dst, 82);
	dst[82] = '\0';
	return (ft_strdup(dst));
}

char	*check_path(char **posible_paths)
{
	int	i;

	i = -1;
	while (posible_paths[++i])
		if (!access(posible_paths[i], F_OK))
			return (posible_paths[i]);
	/*free posible paths*/
	return (NULL);
}

char	*make_path(char *path, char *program)
{
	char	*complete_path;

	complete_path = ft_strjoin(path, program);
	free(path);
	return (complete_path);
}

char	*get_path(char **arg, char **envp)
{
	char	**posible_paths;
	char	*program;
	int		i;

	program = ft_strjoin("/", arg[0]);
	i = 0;
	while (!ft_strnstr(envp[i], "PATH", 4))
		i++;
	posible_paths = ft_split(envp[i] + 5, ':');
	i = -1;
	while (posible_paths[++i])
		posible_paths[i] = make_path(posible_paths[i], program);
	return (check_path(posible_paths));
}

int	execute(char *path, char **argv2, char **envp)
{
	int	error;

	error = execve(path, argv2, envp);
	return (error);
}

char	**get_argv2(char **argv)
{
	char	**argv2;
	char	**spli;

	if (ft_strchr(argv[3], ' '))
	{
		spli = ft_split(argv[3], ' ');
		argv2 = malloc(sizeof(char *) * 3);
		argv2[0] = spli[0];
		argv2[1] = spli[1];
		argv2[2] = NULL;
	}
	else
	{
		argv2 = malloc(sizeof(char *) * 2);
		argv2[0] = ft_strdup(argv[3]);
		argv2[1] = NULL;
	}
	return (argv2);
}

int	main(int argc, char *argv[], char **envp)
{
	char	*argv2[4];
	char	**spli;
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
		if (ft_strchr(argv[2], ' '))
		{
			spli = ft_split(argv[2], ' ');
			argv2[0] = spli[0];
			argv2[1] = spli[1];
			argv2[2] = ft_strdup(argv[1]);
			argv2[3] = NULL;
		}
		else
		{
			argv2[0] = ft_strdup(argv[2]);
			argv2[1] = ft_strdup(argv[1]);
			argv2[2] = NULL;
		}
		execve(ft_strjoin("/bin/", argv2[0]), argv2, envp);
	}
	else
	{
		close(pip[PIPE_WRITE]);
		//printf("pipe in: [%s]\n", real_read(pip[PIPE_READ]));
		/*if (ft_strchr(argv[3], ' '))
		{
			spli = ft_split(argv[3], ' ');
			argv2[0] = spli[0];
			argv2[1] = spli[1];
			argv2[2] = NULL;
		}
		else
		{
			argv2[0] = ft_strdup(argv[3]);
			argv2[1] = NULL;
		}*/
		dst_fd = open(argv[4], O_RDWR | O_TRUNC, 0777);
		dup2(pip[PIPE_READ], STDIN_FILENO);
		close(pip[PIPE_READ]);
		//argv2[1] = real_read(pip[PIPE_READ]);
		pid = fork();
		if (pid == 0)
		{
			printf("argv[3] [%s]\n", argv[3]);
			printf("path [%s]\n", get_path(ft_split(argv[3], ' '), envp));
			printf("dst_fd: [%d]\n", dst_fd);
			dup2(dst_fd, STDOUT_FILENO);
			close(dst_fd);
			execve(get_path(ft_split(argv[3], ' '), envp), get_argv2(argv), envp);
		}
	}
	return (0);
}
