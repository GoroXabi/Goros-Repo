/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xortega <xortega@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 09:16:18 by xortega           #+#    #+#             */
/*   Updated: 2023/09/25 17:02:07 by xortega          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "SUPERLIBFT/libft.h"

//sa: swap_a; intercambia primera y segunda posicion del stack a;
//sb: swap_b; intercambia primera y segunda posicion del stack b;
//ss: swap_ab; intercambia primera y segunda posicion del stack a y b;
//pa: push_a; pasa el argumento mas arriba del stack b a encima del argumento mas arriba del stack a;
//pb: push_b; pasa el argumento mas arriba del stack a a encima del argumento mas arriba del stack b;
//ra: rotate_a; desplaza todos los argumentos del stack a una posicion hacia arrba, el primero pasando a ser el ultimo;
//rb: rotate_b; desplaza todos los argumentos del stack b una posicion hacia arrba, el primero pasando a ser el ultimo;
//rr: rotate_ab; desplaza todos los argumentos del stack a y b una posicion hacia arrba, el primero pasando a ser el ultimo;
//rra: reverse_rotate_a; desplaza todos los argumentos del stack a una posicion hacia abajo, el ultimo pasando a ser el primero;
//rrb: reverse_rotate_b; desplaza todos los argumentos del stack b una posicion hacia abajo, el ultimo pasando a ser el primero;
//rrr: reverse_rotate_ab; desplaza todos los argumentos del stack a y b una posicion hacia abajo, el ultimo pasando a ser el primero;

int	minus(char c)
{
	if (c == '-')
		return (-1);
	return (1);
}

int	i_atoi(const char *str, int k)
{
	static int	count = 0;
	int			c;
	int			m;
	int			j;

	if (k == 0)
		count = 0;
	c = 0;
	m = 1;
	j = 0;
	while (str[count] == ' ' || str[count] == '\n' || str[count] == '-')
		count++;
	while (str[count] != ' ' && str[count] != '\n' \
	&& str[count] != '-' && str[count])
	{
		if (str[count] == '0')
			c *= 10;
		else
			c = (str[count] - 48) + (c * m);
		m *= 10;
		count++;
		j++;
	}
	return (c * minus(str[count - j - 1]));
}

int	count_ints(const char *str)
{
	int	count;
	int	n;

	n = 0;
	count = 0;
	while (str[count])
	{
		if (str[count] == '-')
			count++;
		while (ft_isalnum(str[count]) == 1)
			count++;
		n++;
		while (str[count] == ' ')
			count++;
	}
	return (n);
}

void	fill_stack(int argc, const char **argv, int *stack, int int_count)
{
	int	count_stack;
	int	count_argv;
	int	int_argv;
	int	j;

	count_stack = 0;
	count_argv = 1;
	while (count_stack < int_count)
	{
		while (count_argv < argc)
		{
			j = 0;
			int_argv = count_ints(argv[count_argv]);
			while (int_argv > j)
			{
				stack[count_stack] = i_atoi(argv[count_argv], j);
				j++;
				count_stack++;
			}
			count_argv++;
		}
	}
}

int	main(int argc, char const *argv[])
{
	int	*stack_a;
	int	*stack_b;
	int	int_count;
	int	n;

	if (argc == 1)
		return (0);
	int_count = 0;
	n = 1;
	while (argc > n)
	{
		int_count += count_ints(argv[n]);
		n++;
	}
	stack_a = malloc(sizeof(int) * int_count);
	stack_b = malloc(sizeof(int) * int_count);
	fill_stack(argc, argv, stack_a, int_count);
	n = -1;
	while (int_count > ++n)
		ft_printf("stack_a[%d]: %d\n", n, stack_a[n]);
	return (0);
}
