/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   x_copy.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xortega <xortega@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 11:44:25 by xortega           #+#    #+#             */
/*   Updated: 2023/11/03 12:08:20 by xortega          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "SUPERLIBFT/libft.h"
#include "pipex.h"
#include <unistd.h>

char	*check_path(char **posible_paths)
{
	int		i;
	char	*correct_path;

	i = -1;
	while (posible_paths[++i])
	{	
		if (!access(posible_paths[i], F_OK))
		{
			correct_path = ft_strdup(posible_paths[i]);
			i = -1;
			while (posible_paths[++i])
				free(posible_paths[i]);
			free(posible_paths);
			posible_paths = NULL;
			return (correct_path);
		}
	}
	return (NULL);
}

char	*make_path(char *path, char *program)
{
	char	*complete_path;

	complete_path = ft_strjoin(path, program);
	free(path);
	return (complete_path);
}

char	*g_path(char **arg, char **envp)
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

char	**g_argv(char **argv, int arg)
{
	char	**argv2;
	char	**spli;

	if (ft_strchr(argv[arg], ' '))
	{
		spli = ft_split(argv[arg], ' ');
		argv2 = malloc(sizeof(char *) * 3);
		argv2[0] = spli[0];
		argv2[1] = spli[1];
		argv2[2] = NULL;
	}
	else
	{
		argv2 = malloc(sizeof(char *) * 2);
		argv2[0] = ft_strdup(argv[arg]);
		argv2[1] = NULL;
	}
	return (argv2);
}
int	fd_manager(int c, int *pip, int src_fd, int dst_fd)
{
	if (c == 0)
	{
		close(pip[PIPE_READ]);
		dup2(pip[PIPE_WRITE], STDOUT_FILENO);
		close(pip[PIPE_WRITE]);
		dup2(src_fd, STDIN_FILENO);
		close(src_fd);
		return (0);
	}
	if (c == 1)
	{
		close(pip[PIPE_WRITE]);
		dup2(pip[PIPE_READ], STDIN_FILENO);
		close(pip[PIPE_READ]);
		dup2(dst_fd, STDOUT_FILENO);
		close(dst_fd);
		return (0);
	}
	return (-1);
}

int	open_txt(char *source, char* dest, int *src_fd, int *dst_fd)
{
	*src_fd = open(source, O_RDONLY, 0777);
	*dst_fd = open(dest, O_RDWR | O_TRUNC, 0777);
	if (*dst_fd > 0 && *src_fd > 0)
		return (1);
	else
		return (-1);
}

int	main(int argc, char *argv[], char **envp)
{
	pid_t	pid;
	int		pip[2];
	int		dst_fd;
	int		src_fd;

	if (argc < 2)
		return (0);
	pipe(pip);
	open_txt(argv[1], argv[4], &src_fd, &dst_fd);
	pid = fork();
	if (pid == 0)
	{
		fd_manager(0, pip, src_fd, dst_fd);
		execve(g_path(ft_split(argv[2], ' '), envp), g_argv(argv, 2), envp);
	}
	else
	{
		pid = fork();
		if (pid == 0)
		{
			fd_manager(1, pip, src_fd, dst_fd);
			execve(g_path(ft_split(argv[3], ' '), envp), g_argv(argv, 3), envp);
		}
	}
	return (0);
}