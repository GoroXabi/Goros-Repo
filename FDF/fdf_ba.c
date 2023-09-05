/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_ba.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xortega <xortega@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 10:08:05 by xortega           #+#    #+#             */
/*   Updated: 2023/07/20 12:13:18 by xortega          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "libft.h"
#include "minilibx_macos/mlx.h"

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		***obj;
}				t_data;

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	putpixels(t_data *data)
{
	int	j;
	int	k;
	int	x;
	int	y;

	j = 0;
	k = 0;
	x = 1;
	y = 1;
	while (j < 100)
	{
		k = 0;
		while (k < 500)
		{
			my_mlx_pixel_put(data, k, j, 0x33D1FF);
			k++;
		}
		j++;
	}
		while (j < 200)
	{
		k = 0;
		while (k < 500)
		{
			my_mlx_pixel_put(data, k, j, 0x33B5AA);
			k++;
		}
		j++;
	}
		while (j < 300)
	{
		k = 0;
		while (k < 500)
		{
			my_mlx_pixel_put(data, k, j, 0x33D1FF);
			k++;
		}
		j++;
	}
}

void	sputpixels(t_data *data, char **post)
{
	int	j;
	int	k;
	int	x;
	int	y;
	int	len;
	j = 0;
	k = 0;
	x = 1;
	y = 1;
	len = ft_strlen(post[0]);
	while (post[j] != NULL)
	{
		k = 0;
		x = 0;
		while (post[j][k] != '\0')
		{
			if (post[j][k] == '0')
			{
				// my_mlx_pixel_put(data, (k), (j), 0x33D1FF);
				my_mlx_pixel_put(data, (k + x), (j + y), 0x33D1FF);
				my_mlx_pixel_put(data, (k + x), ((j + y) + 1), 0x33D1FF);
				my_mlx_pixel_put(data, (k + x), ((j + y) + 2), 0x33D1FF);
				my_mlx_pixel_put(data, ((k + x) + 1), (j + y), 0x33D1FF);
				my_mlx_pixel_put(data, ((k + x) + 1), ((j + y) + 1), 0x33D1FF);
				my_mlx_pixel_put(data, ((k + x) + 1), ((j + y) + 2), 0x33D1FF);
				my_mlx_pixel_put(data, ((k + x) + 2), (j + y), 0x33D1FF);
				my_mlx_pixel_put(data, ((k + x) + 2), ((j + y) + 1), 0x33D1FF);
				my_mlx_pixel_put(data, ((k + x) + 2), ((j + y) + 2), 0x33D1FF);
			}
			if (post[j][k] == '1')
			{
				my_mlx_pixel_put(data, (k + x), (j + y), 0x5F6A6E);
				my_mlx_pixel_put(data, (k + x), ((j + y) + 1), 0x5F6A6E);
				my_mlx_pixel_put(data, (k + x), ((j + y) + 2), 0x5F6A6E);
				my_mlx_pixel_put(data, ((k + x) + 1), (j + y), 0x5F6A6E);
				my_mlx_pixel_put(data, ((k + x) + 1), ((j + y) + 1), 0x5F6A6E);
				my_mlx_pixel_put(data, ((k + x) + 1), ((j + y) + 2), 0x5F6A6E);
				my_mlx_pixel_put(data, ((k + x) + 2), (j + y), 0x5F6A6E);
				my_mlx_pixel_put(data, ((k + x) + 2), ((j + y) + 1), 0x5F6A6E);
				my_mlx_pixel_put(data, ((k + x) + 2), ((j + y) + 2), 0x5F6A6E);
			}
			if (post[j][k] == '2')
			{
				my_mlx_pixel_put(data, (k + x), (j + y), 0x32D53F);
				my_mlx_pixel_put(data, (k + x), ((j + y) + 1), 0x32D53F);
				my_mlx_pixel_put(data, (k + x), ((j + y) + 2), 0x32D53F);
				my_mlx_pixel_put(data, ((k + x) + 1), (j + y), 0x32D53F);
				my_mlx_pixel_put(data, ((k + x) + 1), ((j + y) + 1), 0x32D53F);
				my_mlx_pixel_put(data, ((k + x) + 1), ((j + y) + 2), 0x32D53F);
				my_mlx_pixel_put(data, ((k + x) + 2), (j + y), 0x32D53F);
				my_mlx_pixel_put(data, ((k + x) + 2), ((j + y) + 1), 0x32D53F);
				my_mlx_pixel_put(data, ((k + x) + 2), ((j + y) + 2), 0x32D53F);
			}
			if (post[j][k] == '3')
			{
				my_mlx_pixel_put(data, (k + x), (j + y), 0x85B089);
				my_mlx_pixel_put(data, (k + x), ((j + y) + 1), 0x85B089);
				my_mlx_pixel_put(data, (k + x), ((j + y) + 2), 0x85B089);
				my_mlx_pixel_put(data, ((k + x) + 1), (j + y), 0x85B089);
				my_mlx_pixel_put(data, ((k + x) + 1), ((j + y) + 1), 0x85B089);
				my_mlx_pixel_put(data, ((k + x) + 1), ((j + y) + 2), 0x85B089);
				my_mlx_pixel_put(data, ((k + x) + 2), (j + y), 0x85B089);
				my_mlx_pixel_put(data, ((k + x) + 2), ((j + y) + 1), 0x85B089);
				my_mlx_pixel_put(data, ((k + x) + 2), ((j + y) + 2), 0x85B089);
			}
			k++;
			x += 2;
		}
		y += 2;
		j++;
	}
}

int	main(void)
{
	void	*mlx;
	void	*window;
	char	*raw;
	char	**post;
	int		fd;
	t_data	img;

	raw = malloc(sizeof(char) * (16 * 8));
	fd = open("imag.txt", O_RDONLY);
	read(fd, raw, (16 * 8));
	post = ft_split(raw, '\n');
	mlx = mlx_init();
	window = mlx_new_window(mlx, 500, 300, "Prueba");
	img.img = mlx_new_image(mlx, 500, 300);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, \
	&img.line_length, &img.endian);
	sputpixels(&img, post);
	mlx_put_image_to_window(mlx, window, img.img, 0, 0);
	mlx_loop(mlx);
	return (0);
}
