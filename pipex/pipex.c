/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xortega <xortega@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 11:44:25 by xortega           #+#    #+#             */
/*   Updated: 2023/11/03 13:41:27 by xortega          ###   ########.fr       */
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
int	fd_manager(int cas, t_pipex *data)
{
	if (cas == 2)
	{
		close(data->pip[PIPE_READ]);
		dup2(data->pip[PIPE_WRITE], STDOUT_FILENO);
		close(data->pip[PIPE_WRITE]);
		dup2(data->src_fd, STDIN_FILENO);
		close(data->src_fd);
		return (0);
	}
	if (cas == 3)
	{
		close(data->pip[PIPE_WRITE]);
		dup2(data->pip[PIPE_READ], STDIN_FILENO);
		close(data->pip[PIPE_READ]);
		dup2(data->dst_fd, STDOUT_FILENO);
		close(data->dst_fd);
		return (0);
	}
	return (-1);
}

int	open_txt(char *source, char* dest, t_pipex *data)
{
	data->src_fd = open(source, O_RDONLY, 0777);
	data->dst_fd = open(dest, O_RDWR | O_TRUNC, 0777);
	if (data->dst_fd > 0 && data->src_fd > 0)
		return (1);
	else
		return (-1);
}

int	forke(t_pipex *data, int n, char **argv, char **envp)
{
	data->pid = fork();
	if (data->pid == 0)
	{	
		fd_manager(n, data);
		execve(g_path(ft_split(argv[n], ' '), envp), g_argv(argv, n), envp);
	}
	return (0);
}

void imput_errors(int argc, char **argv, char **envp)
{
	if (argc < 5)
	{
		perror("pipex: not enough arguments");
		exit(0);
	}
	if (!(g_path(ft_split(argv[2], ' '), envp)))
	{
		perror("pipex: first command not found\n");
		exit(-1);
	}
	if (!(g_path(ft_split(argv[3], ' '), envp)))
	{
		perror("pipex: second command not found\n");
		exit(-1);
	}
	if (access(argv[1], F_OK))
	{
		perror("pipex: source file not found\n");
		exit(-1);
	}
	if (access(argv[argc - 1], F_OK))
	{
		perror("pipex: destination file not found\n");
		exit(-1);
	}
}

int	main(int argc, char *argv[], char **envp)
{
	//t_pipex	data;

	imput_errors(argc, argv, envp);
	/*pipe(data.pip);
	open_txt(argv[1], argv[4], &data);
	forke(&data, 2, argv, envp);
	forke(&data, 3, argv, envp);*/
	return (0);
}
