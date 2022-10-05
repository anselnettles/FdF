/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviholai <aviholai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 13:30:38 by aviholai          #+#    #+#             */
/*   Updated: 2022/10/05 11:52:09 by aviholai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filsdefer.h"
#include "stdio.h"
#define ERROR_MESSAGES 7

int	error(int errorcode)
{
	const char	*error_messages[ERROR_MESSAGES];

	error_messages[0] = "\033[1;32musage: \"\033[0;37m./fdf <path>\033[1;32m\"";
	error_messages[1] = "\033[1;31mERROR: Could not open the file.";
	error_messages[2] = "\033[1;31mERROR: Could not read the file.";
	error_messages[3] = "\033[1;31mERROR: File contains invalid characters.";
	error_messages[4] = "\033[1;31mERROR: Could not close the file.";
	error_messages[5] = "\033[1;31mERROR: File too large.";
	error_messages[6] = "\033[1;31mERROR: File prints empty.";
	write(1, error_messages[errorcode], ft_strlen(error_messages[errorcode]));
	write(1, "\n", 1);
	return (-1);
}

int	main(int argc, char **argv)
{
	t_vars	v;
	static char	buf[MAX_READ + 1];

	v.fd = 0;
	v.ret = 0;
	v.file = argv[1];
	v.buf = buf;
	if (argc != 2)
		return (error(BAD_ARGS));
	if (validate_file(argv[1], &buf[0], &v) == -1)
		return (-1);
	if (extract_file(&v) == -1)
		return (-1);
	return (0);
}
