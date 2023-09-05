/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_secu2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xortega <xortega@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 11:58:51 by xortega           #+#    #+#             */
/*   Updated: 2023/07/28 14:13:44 by xortega          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

typedef struct s_data
{
	char	*line;
	int		**map;
	int		**color_map;
	int		total_lines;
	int		total_ints;
	int		error;
	int		bigest_int;
	int		atoi_po;
	int		line_po;
}				t_data;

size_t	fdf_size(int n)
{
	size_t	i;

	i = 1;
	if (n < 0)
	{
		n *= -1;
		i++;
	}
	while (n > 9)
	{
		n /= 10;
		i += 1;
	}
	return (i);
}

int	fdf_atoi(const char *str, int j)
{
	int	c;

	c = 0;
	if (str[j] == '0')
		return (0);
	while (str[j])
	{
		if (str[j] >= '0' && str[j] <= '9')
		{
			if (str[j + 1] >= '0' && str[j + 1] <= '9')
				c = (c * 10) + ((str[j] - 48) * 10);
			else
				c += (str[j] - 48);
		}
		if ((str[j + 1] > '9' || str[j + 1] < '0') && c != 0)
			break ;
		j++;
	}
	return (c);
}

int	ints_in_line(char *line)
{
	int	count;
	int	intnbr;
	int	bolean;

	intnbr = 0;
	count = 0;
	bolean = 0;
	while (line[count] != '\n' && line[count])
	{
		if (ft_isalnum(line[count]) == 1 && bolean == 0)
		{
			intnbr++;
			bolean = 1;
		}
		if (line[count] == ' ')
			bolean = 0;
		count++;
	}
	return (intnbr);
}

int	total_lines(char *line)
{
	int	count;
	int	intnbr;

	intnbr = 0;
	count = 0;
	while (line[count])
	{
		if (line[count] == '\n')
			intnbr++;
		count++;
	}
	return (intnbr);
}

void	init_maps(t_data *data)
{
	int	k;

	k = 0;
	data->map = malloc(sizeof(int *) * data->total_lines);
	data->color_map = malloc(sizeof(int *) * data->total_lines);
	while (k < data->total_lines)
	{
		data->map[k] = malloc(sizeof(int) * data->total_ints);
		data->color_map[k] = malloc(sizeof(int) * data->total_ints);
		k++;
	}
}

void	next_postion(t_data *data, int bolean, int lines, int ints)
{
	if (bolean == 0)
	{
		data->line_po++;
		data->atoi_po++;
	}
	if (bolean == 1)
	{
		data->line_po += fdf_size(data->map[lines][ints]);
		data->atoi_po += fdf_size(data->map[lines][ints]);
	}
}

void	fill_map(t_data *data)
{
	int	ints;
	int	lines;

	ints = 0;
	lines = 0;
	while (data->line[data->line_po])
	{
		if (ft_isdigit(data->line[data->line_po]) == 1)
		{
			data->map[lines][ints] = fdf_atoi(data->line, data->atoi_po);
			next_postion(data, 1, lines, ints);
			ints++;
		}
		else if (data->line[data->line_po] == ' ')
			next_postion(data, 0, 0, 0);
		else if (data->line[data->line_po] == '\n')
		{
			ints = 0;
			lines++;
			next_postion(data, 0, 0, 0);
		}
		else
			data->error = 1;
	}
}

void	print_map_list(t_data *data)
{
	int	j;
	int	k;

	k = 0;
	j = 0;
	while (j < data->total_lines)
	{
		while (k < data->total_ints)
		{
			ft_printf("%d%d : %d\n", j, k, data->map[j][k]);
			k++;
		}
		k = 0;
		j++;
	}
}

int	big_size(int **map, int ints, int lines)
{
	int	winner;
	int	foe;
	int	y;
	int	x;

	x = 0;
	y = 0;
	winner = 0;
	while (lines-- > 0)
	{
		while (ints-- > 0)
		{
			foe = fdf_size(map[y][x]);
			if (foe > winner)
				winner = foe;
			x++;
		}
		ints = x;
		x = 0;
		y++;
	}
	return (winner);
}

void	print_map_graph(t_data *data)
{
	int	j;
	int	k;
	int	size;

	ft_printf("ints: %d\n", data->total_ints);
	ft_printf("lines: %d\n", data->total_lines);
	data->bigest_int = big_size(data->map, data->total_ints, data->total_lines);
	ft_printf("BIG: %d\n", data->bigest_int);
	k = 0;
	j = 0;
	while (j < data->total_lines)
	{
		ft_printf("Line %d: ", j);
		if (j < 10)
			ft_printf(" ");
		while (k < data->total_ints)
		{
			ft_printf("%d", data->map[j][k]);
			k++;
			size = fdf_size(data->map[j][k]);
			while (data->bigest_int >= size++)
				ft_printf(" ");
		}
		ft_printf("\n");
		k = 0;
		j++;
	}
}

int main(int argc, char const *argv[])
{
	t_data	data;
	int		fd;

	if (argc != 2)
		return (0);
	fd = open(argv[1], O_RDONLY);
	data.line = ft_calloc(sizeof(char), 1000000);
	read(fd, data.line, 1000000);
	data.total_ints = ints_in_line(data.line);
	data.total_lines = total_lines(data.line);
	init_maps(&data);
	fill_map(&data);
	print_map_graph(&data);
	return (0);
}
