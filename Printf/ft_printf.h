/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xortega <xortega@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 14:32:09 by xortega           #+#    #+#             */
/*   Updated: 2023/06/09 13:55:24 by xortega          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdio.h>
# include <stdarg.h>
# include <unistd.h>
# include "./libft/libft.h"

// %%
int		ft_printf(char const *s, ...);
// %d %i
int		print_number(va_list lst);
// %u
int		print_unsigned(va_list lst);
// %x %X
int		print_hex(va_list lst, char c);
// %s
int		print_string(va_list lst);
// %c
int		print_char(va_list lst);
// %p
int		print_addres(va_list lst);
/////////////////////////////////////
// void	ft_putnbr_fd(int n, int fd);
// void	ft_putstr_fd(char *s, int fd);
// void	ft_putchar_fd(char c, int fd);
// size_t	ft_strlen(const char *str);
#endif
