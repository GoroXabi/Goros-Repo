/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf2.0.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xortega <xortega@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 11:58:51 by xortega           #+#    #+#             */
/*   Updated: 2023/09/05 16:01:32 by xortega          ###   ########.fr       */
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

long int	i_atoi(const char *str)
{
	static long int	count = 0;
	long int		c;
	long int		m;

	c = 0;
	m = 1;
	while (str[count] == ' ' || str[count] == '\n')
		count++;
	while (str[count] != ' ' && str[count] != '\n' && str[count])
	{
		if (str[count] == ',')
		{
			count += 9;
			return (c);
		}	
		if (str[count] == '0')
			c *= 10;
		else
			c = (str[count] - 48) + (c * m);
		m *= 10;
		count++;
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

long int	hex_atoi(const char *str)
{
	static long int	count = 0;
	int				boolean;
	long int		c;

	c = 0x0;
	boolean = 0;
	while (str[count] == ' ' || str[count] == '\n')
		count++;
	while (str[count] != ' ' && str[count] != '\n' && str[count])
	{
		if (str[count] == ',')
		{
			c = 0x0;
			boolean = 1;
			count += 3;
		}
		if (str[count] == '0')
			c *= 0x10;
		else
			c = hex_int(str[count], "0123456789ABCDEF") + (c * 16);
		count++;
	}
	return (c * boolean);
}

long int	ints_in_line(t_data *data, int reset)
{
	static long int	count = 0;
	long int		intnbr;
	long int		boolean;

	intnbr = 0;
	boolean = 0;
	if (reset == 1)
		count = 0;
	while (data->line[count] != '\n' && data->line[count])
	{
		if (ft_isdigit(data->line[count]) == 1 && boolean == 0)
		{
			intnbr++;
			boolean = 1;
		}
		if (data->line[count] == ' ')
			boolean = 0;
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
		data->color_map = malloc(sizeof(int *) * data->total_lines);
	if (!data->map || (data->color == 1 && !data->color_map))
		ft_printf("ERROR MALLOC 1");
	data->total_ints = ints_in_line(data, 1);
	while (k < data->total_lines)
	{
		data->map[k] = malloc(sizeof(long int) * data->total_ints);
		if (data->color == 1)
			data->color_map[k] = malloc(sizeof(long int) * data->total_ints);
		k++;
		data->total_ints = ints_in_line(data, 0);
	}
	if (!data->map[k - 1] || (data->color == 1 && !data->color_map[k - 1]))
		ft_printf("ERROR MALLOC 2\n");
	else
		ft_printf("MALLOC OK\n");
}

void	fill_map(t_data *data)
{
	long int	ints;
	long int	total_ints;
	long int	lines;

	lines = 0;
	ints = 0;
	total_ints = ints_in_line(data, 1);
	while (lines <= data->total_lines)
	{
//		ft_printf("total_ints: %d\n", total_ints);
//		ft_printf("ints: %d\n", ints);
		while (ints < total_ints && total_ints > 0)
		{
			data->map[lines][ints] = i_atoi(data->line);
			if (data->color == 1)
				data->color_map[lines][ints] = hex_atoi(data->line);
//			ft_printf("LINE: %d /INT : %d\n", lines + 1, data->map[lines][ints]);
			ints++;
		}
		total_ints = ints_in_line(data, 0);
		ints = 0;
		lines++;
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

void	print_map(t_data *data)
{
	long int	line_s;
	long int	k;
	long int	ints;
	long int	size;

	k = 0;
	line_s = 0;
	ints = ints_in_line(data, 1);
	while (line_s < data->total_lines)
	{
//		ft_printf("Line %d: ", line_s);
//		if (line_s < 10)
//			ft_printf(" ");
//		if (line_s < 100)
//			ft_printf(" ");
		while (k < ints)
		{
			size = f_size(data->map[line_s][k]);
			while (data->big_int >= size++)
				ft_printf(" ");
			ft_printf("%d", data->map[line_s][k]);
			k++;
		}
		ints = ints_in_line(data, 0);
		ft_printf("\n");
		k = 0;
		line_s++;
	}
}

void	print_color_map(t_data *data)
{
	long int	line_s;
	long int	k;
	long int	ints;
	long int	size;

	k = 0;
	line_s = 0;
	ints = ints_in_line(data, 1);
	while (line_s < data->total_lines)
	{
//		ft_printf("Line %d: ", line_s);
//		if (line_s < 10)
//			ft_printf(" ");
		while (k < ints)
		{
			size = f_size(data->color_map[line_s][k]);
			ft_printf(" ");
			ft_printf("%X", data->color_map[line_s][k]);
			k++;
		}
		ints = ints_in_line(data, 0);
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
	ft_printf("str size: %d\n", data->line_s);
	ft_printf("lines: %d\n", data->total_lines);
	ft_printf("BIG: %d\n", data->big_int);
	ft_printf("posicion (1,1): %d\n", data->map[0][0]);
	ft_printf("map:\n");
	print_map(data);
	if (data->color == 0)
		ft_printf("color: no\n");
	else
	{
		ft_printf("color: yes\n");
		hex = 0xFF0005;
		ft_printf("hex: %X\n", hex);
//		ft_printf("decimal: %d\n", hex);
//		ft_printf("\nprueba color atoi hex: %X\n", hex_atoi("0xFFF"));
		ft_printf("posicion (3,3): %X\n", data->color_map[2][2]);
//		ft_printf("\nprueba color atoi decimal: %d\n", hex_atoi("FFF", 0, 2));
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
