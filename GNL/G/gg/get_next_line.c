/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xortega <xortega@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 09:59:28 by xortega           #+#    #+#             */
/*   Updated: 2023/06/16 14:06:24 by xortega          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 30
#endif

int	ft_strlen(const char *str)
{
	int	c;

	if (!str)
		return (0);
	c = 0;
	while (str[c])
		c++;
	return (c);
}

void	cpy(char *dst, char *src, int s)					//COPIA UN STRING EN OTRO
{
	int	k;

	if (!src)
		return ;
	k = 0;
	while (src[k])
	{
		dst[s] = src[k];
		k++;
		s++;
	}
	dst[s] = '\0';
}

char	*merge(char *first, char *temp, int fd, int *rd)				//CREA UN STRING JUNTANDO DOS STRINGS
{
	char	*dst;
	int		first_len;

	if (first)
		first_len = ft_strlen(first);
	else
		first_len = 0;
	if (*rd != 0)
	{
	*rd = read(fd, temp, BUFFER_SIZE);
	temp[*rd] = '\0';
	}
	dst = malloc(sizeof(char) * (first_len + *rd + 1));
	if (!dst)
		return (NULL);
	if (first)
		cpy(dst, first, 0);
	if (*rd > 0)
		cpy(dst, temp, first_len);
	return (dst);
}

int	search(char *temp, int rd)
{
	int	k;

	if (!temp)
		return (-1);
	k = 0;
	while (temp[k])
	{
		if (temp[k] == '\n')
			return (++k);
		k++;
	}
	if (!temp[k] && rd == 0)
		return (k);
	return (-1);
}

char	*cut(char *all, int nl)								//CREA UN STRING DESDE EL SALTO DE LINEA HASAT EL FINAL DEL STRING RECIBIDO
{
	char	*dst;
	int		k;

	k = 0;
	if ((ft_strlen(all) - nl) <= 0 || !all)
		return (NULL);
	dst = malloc (sizeof(char) * (ft_strlen(all) - nl));
	if (!dst)
		return (NULL);
	while (all[nl] && all)
	{
		dst[k] = all[nl];
		k++;
		nl++;
	}
	return (dst);
}

char	*pack(char *all, int nl)							//CREA UN STRING DESDE EL INICIO DEL STRING RECIBIDO HASTA LA POSICION DEL SALTO DE LINEA
{
	char	*dst;
	int		k;

	dst = NULL;
	k = 0;
	dst = malloc (sizeof(char) * nl);
	if (!dst)
		return (NULL);
	while (k < nl)
	{
		dst[k] = all[k];
		k++;
	}
	return (dst);
}

char	*get_next_line(int fd)
{
	static char			*reminder;
	char				*all;
	char				*fr;
	char				*temp;
	int					nl;
	static int			rd = 1;

	if (rd > 0)
		temp = malloc(sizeof(char) * (BUFFER_SIZE + 1));		//RESERVA MEMORIA PARA  LA LECTURA
	else
		temp = NULL;
	all = merge(reminder, temp, fd, &rd);						//CREA UN STRING CON LO SOBRANTE DE LA LLAMADA ITERACION Y LA NUEVA LECTURA
	nl = search(all, rd);										//BUSCA SALTOS DE LINEA,  DEVUELVE SU HUBICACION O -1
	while (nl <= 0 && all[0] != '\0')							//MIENTRAS EXISTA ALGO QUE ESCRIBIR Y NO SE ENCEUNTRE UN SALTO DE LINEA
	{
		fr = all;												//IGUALA LA POSICION DE MEMORIA PARA LIBERARLA MAS TARDE
		all = merge(fr, temp, fd, &rd);								//CREA UN STRING CON LO SOBRANTE DE LA ANTERIOR ITERACION Y LA NUEVA LECTURA
		free(fr);												//LIBERA LA MEMORIA
		nl = search(all, rd);										//BUSCA DE NUEVO
	}
	temp = NULL;
	free(temp);													//LIBERA LA TEMPORAR DE LECTURA
//	printf("--reminder before: %s--\n", reminder);
	fr = reminder;												//IGUALA LA POSICION DE MEMORIA PARA LIBERARLA MAS TARDE
	reminder = cut(all, nl);									//GUARDA EN LA STATICA UN STRING DEL EL SALTO DE LINEA EN ADELANTE
	free(fr);
	//printf("fr: %s\n", fr);
	printf("pfr: %p\n", fr);
	printf("pall: %p\n", all);
	fr = all;
	free(fr);
	free(all);											//LIBERA LA MEMORIA
//	printf("fr: %s\n", fr);
	printf("pfr: %p\n", fr);
	printf("pall: %p\n", all);
	all = pack(all, nl);
//	printf("fr: %s\n", fr);
	printf("pfr: %p\n", fr);
	printf("pall: %p\n", all);
//	printf("--reminder after: %s--\n", reminder);
//	printf("--TEMP: %s--\n", temp);
//	printf("\n--REMINDER: %s--\n", reminder);
//	printf("--ALL: %s--\n", all);
//	printf("--OUT: %s--\n", fr);
//	printf("--RD: %d--\n", rd);
	return (fr);										//DEVUELVE UN STRING DESDE EEL INICIO HASTA LA POSICION DEL SALTO DE LINEA
}
int	main(void)
{
	int	fd;

	fd = open("../test.txt", O_RDONLY);
	get_next_line(fd);
	printf("----\n");
	// get_next_line(fd);
	// printf("----\n");
	// get_next_line(fd);
	// printf("----\n");
	// get_next_line(fd);
	// printf("----\n");
	// get_next_line(fd);
	// printf("----\n");
	// get_next_line(fd);
	// printf("----\n");
	// get_next_line(fd);
	// printf("----\n");
	// get_next_line(fd);
	// printf("----\n");
	// get_next_line(fd);
	// printf("----\n");
	// get_next_line(fd);
	// printf("----\n");
  	// printf("OUT: %s", get_next_line(fd));
	// printf("----\n");
	// printf("OUT: %s", get_next_line(fd));
	// printf("----\n");
	// printf("OUT: %s", get_next_line(fd));
	// printf("----\n");
	// printf("OUT: %s", get_next_line(fd));
	// printf("----\n");
	// printf("OUT: %s", get_next_line(fd));
	// printf("----\n");
	// printf("OUT: %s", get_next_line(fd));
	// printf("----\n");
	// printf("OUT: %s", get_next_line(fd));
	// printf("----\n");
	// printf("OUT: %s", get_next_line(fd));
	// printf("----\n");
	// printf("OUT: %s", get_next_line(fd));
	// printf("----\n");
	// printf("OUT: %s", get_next_line(fd));
	// printf("----\n");
	// printf("OUT: %s", get_next_line(fd));
	// printf("----\n");
	// printf("OUT: %s", get_next_line(fd));
	// printf("----\n");
	// printf("OUT: %s", get_next_line(fd));
	// printf("----\n");
	// printf("OUT: %s", get_next_line(fd));
	// printf("----\n");
	// printf("OUT: %s", get_next_line(fd));
	// printf("----\n");
	// printf("OUT: %s", get_next_line(fd));
	// printf("----\n");
	// printf("OUT: %s", get_next_line(fd));
	close(fd);
}
