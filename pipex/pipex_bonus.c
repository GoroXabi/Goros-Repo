/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   x_copy.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xortega <xortega@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 11:44:25 by xortega           #+#    #+#             */
/*   Updated: 2023/11/07 17:22:12 by xortega          ###   ########.fr       */
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
	//perror("pipex: command path not found");
	//exit(125);
	return(NULL);
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
		if (!argv2)
			exit (125);
		argv2[0] = spli[0];
		argv2[1] = spli[1];
		argv2[2] = NULL;
	}
	else
	{
		argv2 = malloc(sizeof(char *) * 2);
		if (!argv2)
			exit (125);
		argv2[0] = ft_strdup(argv[arg]);
		argv2[1] = NULL;
	}
	return (argv2);
}

void	open_txt(char *source, char *dest, t_pipex *data)
{
	data->src_fd = open(source, O_RDONLY, 0644);
	data->dst_fd = open(dest, O_RDWR | O_TRUNC | O_CREAT, 0644);
	if (data->dst_fd < 0)
	{
		perror("pipex: destination file couldn't be opened");
		exit(125);
	}
	if (data->src_fd < 0)
	{
		perror("pipex: source file couldn't be opened");
		exit(125);
	}
}
int	src_child(t_pipex *data)
{
	close(data->pip[PIPE_READ]);
	dup2(data->src_fd, STDIN_FILENO);
	close(data->src_fd);
	dup2(data->pip[PIPE_WRITE], STDOUT_FILENO);
	close(data->pip[PIPE_WRITE]);
	return (0);
}

int	dst_child(t_pipex *data)
{
	close(data->pip[PIPE_WRITE]);
	dup2(data->pip[PIPE_READ], STDIN_FILENO);
	close(data->pip[PIPE_READ]);
	dup2(data->dst_fd, STDOUT_FILENO);
	close(data->dst_fd);
	return (0);
}
int	middle_child(t_pipex *data)
{
	dup2(data->pip[PIPE_READ], STDIN_FILENO);
	close(data->pip[PIPE_READ]);
	dup2(data->pip[PIPE_WRITE], STDOUT_FILENO);
	close(data->pip[PIPE_WRITE]);
	return (0);
}

void	forke(t_pipex *data, int cas, char **argv, char **envp)
{
	data->pid = fork();
	pipe(data->pip);
	if (data->pid == 0)
	{	
		if (cas == 2)
			src_child(data);
		//if (cas > 2 && cas < (data->argc - 2))
		//	middle_child(data);
		if (cas == (data->argc - 2))
			dst_child(data);
		//perror(argv[cas]);
		//perror(ft_itoa(cas));
		execve(g_path(ft_split(argv[cas], ' '), envp), g_argv(argv, cas), envp);
		exit(125);
	}
	if (data->pid < 0)
	{
		perror("pipex: fork failed");
		exit(125);
	}
	if (data->pid > 0)
		waitpid(data->pid, NULL, WNOHANG);
}

void imput_errors(int argc, char **argv)
{
	if (argc < 5)
	{
		perror("pipex: not enough arguments");
		exit(22);
	}
	if (access(argv[1], F_OK | R_OK))
	{
		perror("pipex: source file");
		exit(2);
	}
}

int	main(int argc, char *argv[], char **envp)
{
	t_pipex	data;
	//int		i;

	imput_errors(argc, argv);
	data.argc = argc;
	open_txt(argv[1], argv[argc - 1], &data);
	forke(&data, 2, argv, envp);
	/*i = 3;
	while (i < argc - 2)
	{
		forke(&data, i, argv, envp);
		i++;
	}*/
	forke(&data, (argc - 2), argv, envp);
	return (0);
}
