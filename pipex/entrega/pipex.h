/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xortega <xortega@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 13:57:40 by xortega           #+#    #+#             */
/*   Updated: 2023/11/10 15:34:13 by xortega          ###   ########.fr       */
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
# include "SUPERLIBFT/libft.h"

# define PIPE_READ 0
# define PIPE_WRITE 1

typedef struct pipex_struct
{
	int		pip[2];
	pid_t	pid;
	int		dst_fd;
	int		src_fd;
	pid_t	error;
}					t_pipex;

char	*check_path(char **posible_paths);
char	*make_path(char *path, char *program);
char	*get_path(char **arg, char **envp, t_pipex *data, int cas);
void	error_comand(char *arg, int cas, t_pipex *data);
char	**edge_case_quotes(char *arg, t_pipex *data);
char	**double_quotes(char *arg);
char	**single_quotes(char *arg);
char	**get_argv(char *arg, t_pipex *data);
void	fd_manager(int cas, t_pipex *data);
void	open_txt(char *source, char *dest, t_pipex *data);
void	forke(t_pipex *data, int n, char **argv, char **envp);
int		main(int argc, char *argv[], char **envp);

#endif