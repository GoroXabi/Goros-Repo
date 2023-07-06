/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xortega <xortega@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 11:31:35 by xortega           #+#    #+#             */
/*   Updated: 2023/06/01 10:12:34 by xortega          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

static int	magnitudefb(int n)
{
	int	i;

	i = 1;
	if (n < 0)
	n *= -1;
	while (n > 9)
	{
		n /= 10;
		i *= 10;
	}
	return (i);
}

static int	sizefb(int n)
{
	int	i;

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

void	ft_putnbr_fd(int n, int fd)
{
	int		siz;
	int		mag;
	char	c;

	if (fd < 0)
		return ;
	siz = sizefb(n);
	mag = magnitudefb(n);
	if (n == -2147483648)
		write(fd, "-2147483648", 11);
	if (n < 0 && n != -2147483648)
	{
		write(fd, "-", 1);
		n *= -1;
	}
	while (mag > 0 && n != -2147483648)
	{
		c = ((n / mag) + 48);
		write(fd, &c, 1);
		n %= mag;
		mag /= 10;
	}
}
