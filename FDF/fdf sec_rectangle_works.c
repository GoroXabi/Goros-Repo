/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xortega <xortega@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 11:58:51 by xortega           #+#    #+#             */
/*   Updated: 2023/08/30 11:03:57 by xortega          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

typedef struct s_data
{
	char			*line;
	long int		line_po;
	long int		line_s;
	long int		**map;
	long int		**color_map;
	long int		total_lines;
	long int		total_ints;
	long int		color;
	long int		error;
	long int		big_int;
	long int		atoi_space;
}				t_data;

size_t	f_size(long int n)
{
	size_t	i;

	i = 1;
	if (n == 0)
		return (1);
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

long int	i_atoi(const char *str, long int s, long int line_s)
{
	long int	c;
	long int	m;

	c = 0;
	m = 1;
	while (s > 0)
	{
		if (str[line_s] == ' ')
			s--;
		if (str[line_s] == '\n')
			s -= 2;
		line_s--;
	}
	while (line_s >= 0 && str[line_s] != ' ' && str[line_s] != '\n')
	{
		c += (str[line_s] - 48) * m;
		m *= 10;
		if (str[line_s] == ',')
		{
			c = 0;
			m = 1;
		}
		line_s--;
	}
	return (c);
}

long int	hex_int(char c, char *hex)
{
	long int	k;

	k = 16;
	while (k-- > 0)
		if (hex[k] == c)
			return (k);
	return (0);
}

long int	c_atoi(const char *str, long int s, long int line_s)
{
	long int	c;
	long int	m;

	c = 0x0;
	m = 0x1;
	while (s > 0)
	{
		if (str[line_s] == ' ')
			s--;
		if (str[line_s] == '\n')
			s -= 2;
		line_s--;
	}
	while (line_s >= 0 && str[line_s] != ' ' \
	&& str[line_s] != '\n' && str[line_s] != ',')
	{
		c += hex_int(str[line_s], "0123456789ABCDEF") * m;
		//ft_printf("|c = %X|", c);
		m *= 0x10;
		line_s--;
	}
	if (str[line_s] == ',')
		return (c);
	return (0);
}

long int	ints_in_line(char *line)
{
	static long int	count = 0;
	long int		intnbr;
	long int		bolean;

	intnbr = 0;
	bolean = 0;
	while (line[count] != '\n' && line[count])
	{
		if (ft_isdigit(line[count]) == 1 && bolean == 0)
		{
			intnbr++;
			bolean = 1;
		}
		if (line[count] == ' ')
			bolean = 0;
		count++;
	}
	count++;
	return (intnbr);
}

long int	total_lines(char *line)
{
	long int	count;
	long int	linenbr;

	linenbr = 0;
	count = 0;
	while (line[count])
	{
		if (line[count] == '\n')
			linenbr++;
		count++;
	}
	return (linenbr);
}

void	init_maps(t_data *data)
{
	long int	k;

	k = 0;
	data->map = malloc(sizeof(long int *) * data->total_lines);
	if (data->color == 1)
		data->color_map = malloc(sizeof(long int *) * data->total_lines);
	if (!data->map || (data->color == 1 && !data->color_map))
		ft_printf("ERROR MALLOC 1");
	while (k < data->total_lines)
	{
		data->map[k] = malloc(sizeof(long int) * data->total_ints);
		if (data->color == 1)
			data->color_map[k] = malloc(sizeof(long int) * data->total_ints);
		k++;
	}
	if (!data->map[k - 1] || (data->color == 1 && !data->color_map[k - 1]))
		ft_printf("ERROR MALLOC 2\n");
	else
		ft_printf("MALLOC OK\n");
}

void	fill_map(t_data *data)
{
	long int	ints;
	long int	lines;
	long int	spcs;

	lines = data->total_lines - 1;
	spcs = 0;
	while (lines >= 0)
	{
		ints = data->total_ints - 1;
		while (ints >= 0)
		{
			data->map[lines][ints + 1] = i_atoi(data->line, spcs, data->line_s);
			if (data->color == 1)
				data->color_map[lines][ints + 1] = \
				c_atoi(data->line, spcs, data->line_s);
			spcs += (data->big_int - f_size(data->map[lines][ints + 1]) + 1);
			ints--;
		}
		lines--;
	}
}

void	big_size(t_data *data, long int line_s)
{
	long int	winner;
	long int	foe;

	foe = 0;
	winner = 0;
	while (data->line[line_s])
	{
		if (data->line[line_s] != ' ' && data->line[line_s] != '\n')
		{
			foe++;
			if (data->line[line_s] == ',')
				foe = 0;
		}
		else
		{
			if (foe > winner)
				winner = foe;
			foe = 0;
		}
		line_s--;
	}
	data->big_int = winner;
}

void	print_map_graph(t_data *data)
{
	long int	line_s;
	long int	k;
	long int	size;

	k = 0;
	line_s = 0;
	while (line_s < data->total_lines)
	{
		ft_printf("Line %d: ", line_s);
		if (line_s < 10)
			ft_printf(" ");
		while (k < data->total_ints)
		{
			size = f_size(data->map[line_s][k]);
			while (data->big_int >= size++)
				ft_printf(" ");
			ft_printf("%d", data->map[line_s][k]);
			k++;
		}
		ft_printf("\n");
		k = 0;
		line_s++;
	}
}

void	print_color_map(t_data *data)
{
	long int	line_s;
	long int	k;
	long int	size;

	k = 0;
	line_s = 0;
	while (line_s < data->total_lines)
	{
		ft_printf("Line %d: ", line_s);
		if (line_s < 10)
			ft_printf(" ");
		while (k < data->total_ints)
		{
			size = f_size(data->color_map[line_s][k]);
			ft_printf(" ");
			ft_printf("%X", data->color_map[line_s][k]);
			k++;
		}
		ft_printf("\n");
		k = 0;
		line_s++;
	}
}

void	color(t_data *data)
{
	long int	k;

	k = 0;
	while (data->line[k])
	{
		if (data->line[k] == ',')
			data->color = 1;
		k++;
	}
}
void print(t_data *data)
{
	long int		hex;

	ft_printf("hola\n");
	ft_printf("prueba atoi: %d\n", i_atoi("121,F34\n12,GD21 1,FFFF", 0, 6));
	ft_printf("str size: %d\n", data->line_s);
	ft_printf("ints: %d\n", data->total_ints);
	ft_printf("lines: %d\n", data->total_lines);
	ft_printf("BIG: %d\n", data->big_int);
	ft_printf("posicion (3,3): %d\n", data->map[2][2]);
	ft_printf("map:\n");
	print_map_graph(data);
	if (data->color == 0)
		ft_printf("color: no\n");
	else
	{
		ft_printf("color: yes\n");
		hex = 0xFFF;
		ft_printf("hex: %X\n", hex);
//		ft_printf("decimal: %d\n", hex);
		ft_printf("\nprueba color atoi hex: %X\n", c_atoi("FFF", 0, 2));
		ft_printf("posicion (3,3): %X\n", data->color_map[2][2]);
//		ft_printf("\nprueba color atoi decimal: %d\n", c_atoi("FFF", 0, 2));
		ft_printf("color map:\n");
		print_color_map(data);
	}
}

int main(int argc, char const *argv[])
{
	t_data			data;
	long int		fd;

	if (argc != 2)
		return (0);
	fd = open(argv[1], O_RDONLY);
	data.line = ft_calloc(sizeof(char), 3000000);
	read(fd, data.line, 3000000);
	data.line_s = ft_strlen(data.line) - 1;
	ft_printf("strsize %d\n", data.line_s);
	color(&data);
	ft_printf("color %d\n", data.color);
	data.total_ints = ints_in_line(data.line);
	ft_printf("ints %d\n", data.total_ints);
	data.total_lines = total_lines(data.line);
	ft_printf("lines %d\n", data.total_lines);
	big_size(&data, data.line_s);
	ft_printf("biggest int %d\n", data.big_int);
	init_maps(&data);
	fill_map(&data);
	ft_printf("map?: %d\n", data.map[2][2]);
	print(&data);
	return (0);
}
