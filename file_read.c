/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_read.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviholai <aviholai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 18:08:59 by aviholai          #+#    #+#             */
/*   Updated: 2022/09/22 16:24:31 by aviholai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filsdefer.h"
#include <stdio.h>

//t_vars get_vars()
//{
/*	static t_vars vars;

	return vars;
}

size_t get_cunt()
{
	static size_t cunt = 0;

	return (cunt);

void init_vars(t_vars *vars)
{
	vars->newline_count = 0;
}

static int	nl_count(char *buf)
{
	t_vars	vars;
	int		i;
	i = 0;
	vars = get_vars();
	init_vars(vars);
	printf("\n\nnewlinecount: %zd", vars.newline_count);
	cunt++;
	while (buf[i])
	{
		if (buf[i] == '\n')
		{
			vars.newline_count += 1;
			printf("Found newline %zd. ", vars.newline_count);
		}
		i++;
	}
	if (vars.newline_count <= 0)
		return (error(INVALID_CHARS));
	else
		return (0);
}
*/


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
		//if ((buf[i] == ' ' && buf[i - 1] != ' ' && buf[i - 1] != '\n' && j != 0)
		//	|| (buf[i] == '\n' && buf[i - 1] != ' ')
		//	|| (buf[i] == '\0' && buf[i - 1] != ' '))
		//{
		//	total_coordinates++;
		//	printf("\033[1;32mC:#%zu. \033[1;37m", total_coordinates);
		//}
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
