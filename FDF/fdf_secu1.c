/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xortega <xortega@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 11:58:51 by xortega           #+#    #+#             */
/*   Updated: 2023/07/28 10:47:11 by xortega          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

typedef struct s_data
{
	char	*line;
	int		**map;
	int		**color_map;
	int		lines;
	int		ints;
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

int	**init_map(char *line)
{
	int		**map;
	size_t	k;
	size_t	ints;
	size_t	lines;

	k = 0;
	ints = ints_in_line(line);
	lines = total_lines(line);
	map = malloc(sizeof(int *) * lines);
	while (k < lines)
	{
		map[k] = malloc(sizeof(int) * ints);
		k++;
	}
	return (map);
}

int	**fill_map(char *line)
{
	int	ints;
	int	line_po;
	int	lines;
	int	atoi_po;
	int	**map;

	ints = 0;
	lines = 0;
	line_po = 0;
	atoi_po = 0;
	map = init_map(line);
	while (line[line_po])
	{
		if (ft_isdigit(line[line_po]) == 1)
		{
			map[lines][ints] = fdf_atoi(line, atoi_po);
			line_po += fdf_size(map[lines][ints]);
			atoi_po += fdf_size(map[lines][ints]);
			ints++;
		}
		else if (line[line_po] == ' ')
		{
			line_po++;
			atoi_po++;
		}
		else if (line[line_po] == '\n')
		{
			ints = 0;
			lines++;
			line_po++;
			atoi_po++;
		}
		else
			return (NULL);
	}
	return (map);
}

void	print_map_list(int **map, char *line)
{
	size_t	j;
	size_t	k;
	size_t	ints;
	size_t	lines;

	ints = ints_in_line(line);
	lines = total_lines(line);
	k = 0;
	j = 0;
	while (j < lines)
	{
		while (k < ints)
		{
			ft_printf("%d%d : %d\n", j, k, map[j][k]);
			k++;
		}
		k = 0;
		j++;
	}
}

size_t	big_size(int **map, int ints, int lines)
{
	size_t	winner;
	size_t	foe;
	int		y;
	int		x;

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

void	print_map_graph(int **map, char *line)
{
	size_t	j;
	size_t	k;
	size_t	big_int;
	size_t	size;
	size_t	ints;
	size_t	lines;

	ints = ints_in_line(line);
	lines = total_lines(line);
	ft_printf("ints: %d\n", ints);
	ft_printf("lines: %d\n", lines);
	big_int = big_size(map, ints, lines);
	ft_printf("BIG: %d\n", big_int);
	k = 0;
	j = 0;
	while (j < lines)
	{
		ft_printf("Line %d: ", j);
		if (j < 10)
			ft_printf(" ");
		while (k < ints)
		{
			ft_printf("%d", map[j][k]);
			k++;
			size = fdf_size(map[j][k]);
			while (big_int >= size++)
				ft_printf(" ");
		}
		ft_printf("\n");
		k = 0;
		j++;
	}
}

int	main(void)
{
	int		**map;
	char	*line;
	int		fd;

	fd = open("maps/mars.fdf", O_RDONLY);
//	fd = open("map.txt", O_RDONLY);
	line = ft_calloc(sizeof(char), 1000000);
	read(fd, line, 1000000);
	map = fill_map(line);
	print_map_graph(map, line);
	//obj = ft_split(line, '\n');
	//ft_printf("%s", obj[1]);
	return (0);
}
