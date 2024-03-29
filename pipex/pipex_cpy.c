/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_cpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xortega <xortega@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 11:44:25 by xortega           #+#    #+#             */
/*   Updated: 2023/11/10 15:17:26 by xortega          ###   ########.fr       */
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
	i = -1;
	while (posible_paths[++i])
		free(posible_paths[i]);
	free(posible_paths);
	posible_paths = NULL;
	return (NULL);
}

char	*make_path(char *path, char *program)
{
	char	*complete_path;

	complete_path = ft_strjoin(path, program);
	free(path);
	return (complete_path);
}

void	error_comand(char *arg, int cas, t_pipex *data)
{
	ft_putstr_fd("pipex: ", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(": command not found\n", 2);
	if (cas > 2)
		data->error = 127;
}

char	*get_path(char **arg, char **envp, t_pipex *data, int cas)
{
	char	**posible_paths;
	char	*correct_path;
	char	*program;
	int		i;

	if (arg[0][0] == '.')
		return (ft_strjoin(ft_strjoin(arg[0], " "), arg[1]));
	program = ft_strjoin("/", arg[0]);
	i = 0;
	while (!ft_strnstr(envp[i], "PATH", 4))
		i++;
	posible_paths = ft_split(envp[i] + 5, ':');
	i = -1;
	while (posible_paths[++i])
		posible_paths[i] = make_path(posible_paths[i], program);
	free(program);
	correct_path = check_path(posible_paths);
	if (!correct_path)
		return (error_comand(arg[0], cas, data), ft_strdup(""));
	return (correct_path);
}

char	**nigthmare_quotes(char *arg, t_pipex *data)
{
	char	**spli;
	char	*temp;

	if (ft_strchr(arg, '"') > ft_strchr(arg, '\''))
	{	
		spli = ft_split(arg, '\'');
		temp = ft_strdup(spli[0]);
		free (spli[0]);
		spli[0] = ft_strtrim(temp, " ");
		free (temp);
		return (spli);
	}
	else
	{
		spli = ft_split(arg, '\"');
		temp = ft_strdup(spli[0]);
		free (spli[0]);
		spli[0] = ft_strtrim(temp, " ");
		free (temp);
		data->error = 2;
		return (spli);
	}
	return (NULL);
}
char	**double_quotes(char *arg)
{
	char	**spli;
	char	*temp;

	spli = ft_split(arg, '\'');
	temp = ft_strdup(spli[0]);
	free (spli[0]);
	spli[0] = ft_strtrim(temp, " ");
	free (temp);
	return (spli);
}
char	**single_quotes(char *arg)
{
	char	**spli;
	char	*temp;

	spli = ft_split(arg, '"');
	temp = ft_strdup(spli[0]);
	free (spli[0]);
	spli[0] = ft_strtrim(temp, " ");
	free (temp);
	return (spli);
}

char	**get_argv(char *arg, t_pipex *data)
{
	if (arg[0] == '.')
		return (ft_split(arg, '\0'));
	if (ft_strchr(arg, '"') && ft_strchr(arg, '\''))
		return (nigthmare_quotes(arg, data));
	else if (ft_strchr(arg, '\''))
		return (double_quotes(arg));
	else if (ft_strchr(arg, '"'))
		return (single_quotes(arg));
	else
		return (ft_split(arg, ' '));
	return (NULL);
}

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

void	open_txt(char *source, char* dest, t_pipex *data)
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
	ft_putstr_fd(path, 2);
	ft_putstr_fd("\n", 2);
	ft_putstr_fd(arguments[0], 2);
	ft_putstr_fd("\n", 2);
	ft_putstr_fd(arguments[1], 2);
	ft_putstr_fd("\n", 2);
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
