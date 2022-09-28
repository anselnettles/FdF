/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviholai <aviholai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 18:08:59 by aviholai          #+#    #+#             */
/*   Updated: 2022/09/28 12:19:35 by aviholai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filsdefer.h"
#include <stdio.h>

static int	symbol_validation(char *buf, size_t ret)
{
	size_t		total_newlines;
	size_t		i;
	static int	j = 0;

	i = 0;
	total_newlines = 0;
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
			total_newlines++;
			printf("Found newline %zu. ", total_newlines);
		}
		i++;
		j++;
	}
	return (total_newlines);
}

int	validate_file(const char *file, char *buf)
{
	int				fd;
	ssize_t			ret;
	static ssize_t	total_newlines;

	total_newlines = 0;
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
		total_newlines += symbol_validation(buf, ret);
		ret = read(fd, buf, MAX_READ);
	}
	//I STILL NEED A CHECK FOR THAT LAST COORDINATE IN PYRAMIDE.
	if (close(fd) == -1)
		return (error(CLOSE_FAIL));
	printf("Total newlines: %zu. ", total_newlines);
	if (total_newlines == 0)
		return (error(INVALID_CHARS));
	return (total_newlines);
}
