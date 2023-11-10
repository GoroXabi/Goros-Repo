/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_get_path.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xortega <xortega@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 15:30:24 by xortega           #+#    #+#             */
/*   Updated: 2023/11/10 15:32:57 by xortega          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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
		return (arg[0]);
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
