/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviholai <aviholai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 18:08:59 by aviholai          #+#    #+#             */
/*   Updated: 2022/10/06 11:32:17 by aviholai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filsdefer.h"
#include <stdio.h>

static int	file_cancel(t_vars *v)
{
	if (v->read_newlines <= 0)
		return (error(NO_NL));
	if (!v->read_numbers)
		return (error(NO_PRINT));
	return (0);
}

static int	symbol_validation(char *buf, ssize_t ret, t_vars *v)
{
	ssize_t		i;
	static int	j = 0;

	i = 0;
	//printf("The length of 'ret' is %zu.\n", ret);
	while (i < ret)
	{
	//	printf("I#%d. ", j);
		if (buf[i] < ',' || buf[i] > 'F')
		{
			if (buf[i] != ' ' && buf[i] != 'x' && buf[i] != '\n')
			{
	//			printf("It is in the large scope. It is not ' ', 'x' or a newline. ");
				return (error(INVALID_CHARS));
			}
		}
		if (buf[i] == '.' || buf[i] == '/')
		{
	//		printf("There is a '.' or a '/' ");
			return (error(INVALID_CHARS));
		}
		if (buf[i] > '9' && buf[i] < 'A')
		{
	//		printf("There is something between '9' and 'A'. ");
			return (error(INVALID_CHARS));
		}
		if (buf[i] == '\n')
		{
			v->read_newlines++;
	//		printf("Found newline %d. ", v->read_newlines);
		}
		if (buf[i] >= '0' && buf[i] <= '9')
			v->read_numbers = 1;
		i++;
		j++;
	}
	if (j > MAX_READ)
		return (error(FILE_MAX));
	return (0);
}

int	validate_file(const char *file, char *buf, t_vars *v)
{
	int				fd;
	ssize_t			ret;
	
	v->read_newlines = 0;
	v->read_numbers = 0;
	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (error(OPEN_FAIL));
	ret = read(fd, buf, MAX_READ);
	if (ret < 0)
		return (error(READ_FAIL));
	if (ret > MAX_READ)
		return (error(FILE_MAX));
	while (ret > 0)
	{
		buf[ret] = '\0';
		if (symbol_validation(buf, ret, v) == -1)
			return (-1);
		ret = read(fd, buf, MAX_READ);
	}
	if (file_cancel(v) == -1)
		return (-1);
	if (close(fd) == -1)
		return (error(CLOSE_FAIL));
	return (0);
}
