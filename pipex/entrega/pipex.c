/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xortega <xortega@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 11:44:25 by xortega           #+#    #+#             */
/*   Updated: 2023/11/10 15:34:52 by xortega          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	fd_manager(int cas, t_pipex *data)
{
	if (cas == 2)
	{
		close(data->pip[PIPE_READ]);
		dup2(data->pip[PIPE_WRITE], STDOUT_FILENO);
		close(data->pip[PIPE_WRITE]);
		dup2(data->src_fd, STDIN_FILENO);
		close(data->src_fd);
	}
	if (cas == 3)
	{
		close(data->pip[PIPE_WRITE]);
		dup2(data->pip[PIPE_READ], STDIN_FILENO);
		close(data->pip[PIPE_READ]);
		dup2(data->dst_fd, STDOUT_FILENO);
		close(data->dst_fd);
	}
}

void	open_txt(char *source, char *dest, t_pipex *data)
{
	data->src_fd = open(source, O_RDONLY | O_CREAT, 0644);
	data->dst_fd = open(dest, O_RDWR | O_TRUNC | O_CREAT, 0644);
}

void	forke(t_pipex *data, int n, char **argv, char **envp)
{
	char	**arguments;
	char	*path;
	int		i;

	i = -1;
	arguments = get_argv(argv[n], data);
	path = get_path(ft_split(argv[n], ' '), envp, data, n);
	data->pid = fork();
	if (data->pid == 0)
	{	
		fd_manager(n, data);
		execve(path, arguments, envp);
		exit(2);
	}
	if (data->pid < 0)
		exit(2);
	if (data->pid > 0)
	{
		while (arguments[++i])
			free(arguments[i]);
		free(arguments);
		if (path)
			free(path);
		waitpid(data->pid, NULL, WNOHANG);
	}
}

int	main(int argc, char *argv[], char **envp)
{
	t_pipex	data;

	if (argc < 5)
	{
		ft_putstr_fd("pipex: not enough arguments", 2);
		exit(2);
	}
	if (!*envp)
		envp[0] = strdup("PATH=/bin:/usr/bin:");
	data.error = 0;
	pipe(data.pip);
	open_txt(argv[1], argv[4], &data);
	forke(&data, 2, argv, envp);
	forke(&data, 3, argv, envp);
	return (data.error);
}
