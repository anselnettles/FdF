/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviholai <aviholai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 13:30:38 by aviholai          #+#    #+#             */
/*   Updated: 2022/09/12 14:24:21 by aviholai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "filsdefer.h"
#include <unistd.h>
#include <string.h>
#define ERROR_MESSAGES 2

typedef enum e_error
{
	BAD_ARGS,
	OPEN_FAIL,
	READ_FAIL,
}	t_error;

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (s[len] != '\0')
		len++;
	return (len);
}

int	error(int errorcode)
{
	const char	*error_messages[ERROR_MESSAGES];

	error_messages[0] = "usage: \"./fdf <path>\"";
	error_messages[1] = "error";
	write(1, error_messages[errorcode], ft_strlen(error_messages[errorcode]));
	write(1, "\n", 1);
	return (-1);
}

int	main(int argc, char **argv)
{
	char	total_coordinates;

	if (argc != 2)
		return (error(BAD_ARGS));
//	total_coordinates = validate_file(argv[1], &buf[0]);
	if (total_coordinates == -1)
		return (error(-1));
	return (0);
}
