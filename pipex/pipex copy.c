/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xortega <xortega@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 11:44:25 by xortega           #+#    #+#             */
/*   Updated: 2023/10/25 15:09:22 by xortega          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "SUPERLIBFT/libft.h"
#include "pipex.h"

void	printstruct(t_list *comands)
{
	int	n;

	n = 1;
	while (comands)
	{
		printf("comando numero %d: %s\n", n++, comands->content);
		comands = comands->next;
	}
}

int	main(int argc, char *argv[], char **envp)
{
	t_list		*commands;
	pid_t		pid;
	int			pip[2];
	int			n;			

	if (argc < 3)
		return (0);
	commands = ft_lstnew((void *)argv[n]);
	while ((argc - 1) > ++n)
		ft_lstadd_back(&commands, ft_lstnew((void *)argv[n]));
	n = execve(ft_strjoin("/bin/", "cat"), argv, envp);
	return (0);
}
