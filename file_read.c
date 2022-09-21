/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_read.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviholai <aviholai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 18:08:59 by aviholai          #+#    #+#             */
/*   Updated: 2022/09/21 14:54:25 by aviholai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filsdefer.h"
#include <stdio.h>

int			get_newline(char *buf)
{
	ssize_t	i;

	i = 0;
	while (buf[i])
	{
		if (buf[i] == '\n')
		return (i);
		i++;
	}
	return (error(INVALID_CHARS));
}

static int	symbol_validation(char *buf, size_t ret)
{
	size_t		total_coordinates;
	size_t		i;
	static int	j = 0;

	i = 0;
	total_coordinates = 0;
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
		if ((buf[i] == ' ' && buf[i - 1] != ' ' && buf[i - 1] != '\n' && j != 0)
			|| (buf[i] == '\n' && buf[i - 1] != ' ')
			|| (buf[i] == '\0' && buf[i - 1] != ' '))
		{
			total_coordinates++;
			printf("\033[1;32mC:#%zu. \033[1;37m", total_coordinates);
		}
		i++;
		j++;
	}
	return (total_coordinates);
}

int	validate_file(const char *file, char *buf)
{
	int				fd;
	ssize_t			ret;
	static ssize_t	total_coordinates;
	t_vars			vars;

	total_coordinates = 0;
	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (error(OPEN_FAIL));
	ret = read(fd, buf, MAX_READ);
	if (ret < 0)
		return (error(READ_FAIL));
	if (ret > MAX_READ)
		return (error(FILE_MAX));
	vars.newline_index = get_newline(buf);
	while (ret > 0)
	{
		buf[ret] = '\0';
		total_coordinates += symbol_validation(buf, ret);
		ret = read(fd, buf, MAX_READ);
	}
	//I STILL NEED A CHECK FOR THAT LAST COORDINATE IN PYRAMIDE.
	if (close(fd) == -1)
		return (error(CLOSE_FAIL));
	printf("Total coordinates: %zu. ", total_coordinates);
	if (total_coordinates == 0)
		return (error(NO_PRINT));
	return (total_coordinates);
}
