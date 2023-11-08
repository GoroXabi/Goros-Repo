/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xortega <xortega@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 11:44:25 by xortega           #+#    #+#             */
/*   Updated: 2023/11/08 12:11:51 by xortega          ###   ########.fr       */
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

char	*get_path(char **arg, char **envp, t_pipex *data, int cas)
{
	char	**posible_paths;
	char	*correct_path;
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
	correct_path = check_path(posible_paths);
	if (!correct_path)
	{
		ft_putstr_fd("pipex: ", 2);
		ft_putstr_fd(arg[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		if (cas > 2)
			data->error = 127;
	}
	return (correct_path);
}

char	**get_argv(char **argv, int arg)
{
	char	**argv2;
	char	**spli;
	char	*temp;

	if (ft_strchr(argv[arg], '"'))//hazlo alreves primero splitea espacios y luego trimea commilas
	{
		spli = ft_split(argv[arg], '"');
		temp = ft_strdup(spli[0]);
		free (spli[0]);
		spli[0] = ft_strtrim(temp, " ");
		return (free (temp), spli);
	}
	else if (ft_strchr(argv[arg], ' '))
		return (spli = ft_split(argv[arg], ' '));
	else if (ft_strchr(argv[arg], '\''))
		return (spli = ft_split(argv[arg], '\''));
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

void	open_txt(char *source, char* dest, t_pipex *data)
{
	data->src_fd = open(source, O_RDONLY, 0644);
	data->dst_fd = open(dest, O_RDWR | O_TRUNC | O_CREAT, 0644);
}

void	forke(t_pipex *data, int n, char **argv, char **envp)
{
	char	**arguments;
	char	*path;

	arguments = get_argv(argv, n);
	path = get_path(ft_split(argv[n], ' '), envp, data, n);
	data->pid = fork();
	if (data->pid == 0)
	{	
		fd_manager(n, data);
		execve(path, arguments, envp);
		exit(125);
	}
	if (data->pid < 0)
		exit(2);
	if (data->pid > 0)
		waitpid(data->pid, NULL, WNOHANG);
}

int	main(int argc, char *argv[], char **envp)
{
	t_pipex	data;

	if (argc < 5)
	{
		perror("pipex: not enough arguments");
		exit(2);
	}
	data.error = 0;
	pipe(data.pip);
	open_txt(argv[1], argv[4], &data);
	forke(&data, 2, argv, envp);
	forke(&data, 3, argv, envp);
	return (data.error);
}
