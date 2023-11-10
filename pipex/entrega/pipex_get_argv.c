/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_get_argv.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xortega <xortega@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 15:30:24 by xortega           #+#    #+#             */
/*   Updated: 2023/11/10 15:34:39 by xortega          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**edge_case_quotes(char *arg, t_pipex *data)
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
	char	**argv2;
	char	**spli;

	if (ft_strchr(arg, '"') && ft_strchr(arg, '\''))
		return (edge_case_quotes(arg, data));
	else if (ft_strchr(arg, '\''))
		return (double_quotes(arg));
	else if (ft_strchr(arg, '"'))
		return (single_quotes(arg));
	else
		return (spli = ft_split(arg, ' '));
	return (argv2);
}
