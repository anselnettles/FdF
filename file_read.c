/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_read.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviholai <aviholai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 18:08:59 by aviholai          #+#    #+#             */
/*   Updated: 2022/09/13 18:13:19 by aviholai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filsdefer.h"
#include <stdio.h>

static int	symbol_validation(char *buf, size_t ret)
{
	size_t	i;

	i = 0;
	printf("The length of 'ret' is %zu. ", ret);
	while (i < ret - 1)
	{
		printf("Loop #%zu. ", i);
		if (buf[i] < ',' || buf[i] > 'F')
		{
			if (buf[i] != ' ' && buf[i] != 'x' && buf[i] != '\n')
			{
				printf("It is not ' ', 'x' or a newline. ");
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
		i++;
	}
	return (0);
}

int	validate_file(const char *file, char *buf)
{
	int		fd;
	ssize_t	ret;
	char	total_coordinates;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (error(OPEN_FAIL));
	ret = read(fd, buf, MAX_READ + 1);
	if (ret < 0)
		return (error(READ_FAIL));
	if (close(fd) == -1)
		return (error(CLOSE_FAIL));
	buf[ret] = 0;
	if (ret > MAX_READ)
		return (error(FILE_MAX));
	if (symbol_validation(buf, ret) == -1)
	{
		printf("Symbol_validation equals -1.");
		return (-1);
	}
//	if (total_coordinates == 0)
//		return (error(NO_PRINT));
	return (total_coordinates);
}
