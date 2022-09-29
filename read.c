/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviholai <aviholai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 18:08:59 by aviholai          #+#    #+#             */
/*   Updated: 2022/09/29 18:41:51 by aviholai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filsdefer.h"
#include <stdio.h>

static int	symbol_validation(char *buf, ssize_t ret, t_vars *v)
{
	ssize_t		i;
	static int	j = 0;

	i = 0;
	v->total_newlines = 0;
	printf("The length of 'ret' is %zu.\n", ret);
	while (i < ret)
	{
		printf("I#%d. ", j);
		if (buf[i] < ',' || buf[i] > 'F')
		{
			if (buf[i] != ' ' && buf[i] != 'x' && buf[i] != '\n')
			{
				printf("It is in the large scope. It is not ' ', 'x' or a newline. ");
				return (error(INVALID_CHARS));
			}
		}
		if (buf[i] == '.' || buf[i] == '/')
		{
			printf("There is a '.' or a '/' ");
			return (error(INVALID_CHARS));
		}
		if (buf[i] > '9' && buf[i] < 'A')
		{
			printf("There is something between '9' and 'A'. ");
			return (error(INVALID_CHARS));
		}
		if (buf[i] == '\n')
		{
			v->total_newlines++;
			printf("Found newline %d. ", v->total_newlines);
		}
		i++;
		j++;
	}
	return (0);
}

int	validate_file(const char *file, char *buf, t_vars *v)
{
	int				fd;
	ssize_t			ret;

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
		symbol_validation(buf, ret, v);
		ret = read(fd, buf, MAX_READ);
	}
	//I STILL NEED A CHECK FOR THAT LAST COORDINATE IN PYRAMIDE.
	if (close(fd) == -1)
		return (error(CLOSE_FAIL));
	if (v->total_newlines == 0)
		return (error(INVALID_CHARS));
	return (0);
}
