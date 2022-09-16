/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_extract.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviholai <aviholai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 12:04:53 by aviholai          #+#    #+#             */
/*   Updated: 2022/09/16 12:55:53 by aviholai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filsdefer.h"
#include <stdio.h>

int	extract_file(const char *file, char *buf, int total_coordinates)
{
	int		fd;
	ssize_t	ret;

	printf("\n\nWelcome to extract_file(). \nSo, total_coordinates is %d\n",
			total_coordinates);
	fd = open(file, O_RDONLY);
	ret = read(fd, buf, MAX_READ);
	while (ret)
	{
		buf[ret] = '\0';
		printf("|Buf0:%c", buf[0]);
		printf("|Buf1:%c", buf[1]);
		printf("|Buf2:%c", buf[2]);
		printf("|Buf3:%c", buf[3]);
		printf("|Buf4:%c", buf[4]);
		printf("|Buf5:%c", buf[5]);
		printf("|Buf6:%c", buf[6]);
		printf("|Buf7:%c", buf[7]);
		printf("|Buf8:%c", buf[8]);
		printf("|Buf9:%c", buf[9]);
		ret = read(fd, buf, MAX_READ);
	}
	return(0);
}
