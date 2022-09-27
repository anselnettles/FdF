/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_01.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviholai <aviholai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 15:50:39 by aviholai          #+#    #+#             */
/*   Updated: 2022/09/27 16:24:04 by aviholai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filsdefer.h"
#include <stdio.h>

int	parallel_projection()
{
	int		i;
	int		i2;
	int		i3;
	char	*coordinate;
	int		x_pos;
	int		y_pos;
	int		depth;
	int		color;

	while (ret && (vars.parallel_mode == PARALLEL_TRUE || vars.parallel_mode == PARALLEL_FALSE))
	{
		buf[ret] = '\0';
		i = 0;
		while (i < MAX_READ)
		{
			printf("\n| Buf: %d | Char: %c", i, buf[i]);
			//IF BUF INDEX IS AT A COORDINATE:
			if (buf[i] != ' ' && buf[i] != '\n' && buf[i] != '\t' &&  buf[i])
			{
				coordinate = (char *)malloc(sizeof(char)*(ft_strlen(buf) + 1));
				i3 = 0;
				while (buf[i] != ' ' && buf[i] != '\n' && buf[i])
				{
					coordinate[i3] = buf[i];
					i++;
					i3++;
				}
				while (coordinate[i3])
				{
					coordinate[i3] = '\0';
					i3++;
				}
				depth = depth_parser(coordinate);
				color = color_parser(coordinate, depth);
				if (vars.parallel_mode == PARALLEL_TRUE)
					mlx_pixel_put(vars.mlx, vars.win, x_pos, y_pos, color);
				if (vars.parallel_mode == PARALLEL_FALSE)
					isometric(x_pos, y_pos, color);
				x_pos += INCREMENT;
			}
			if (buf[i] == '\n')
			{
				total_newlines--;
				x_pos = START_POSITION;
				y_pos += INCREMENT;
				if (vars.parallel_mode == PARALLEL_FALSE)
				{
					// MOVE THE CURSOR BACK UP IN RELATION TO NUMBER OF X AXIS COORDINATES
					// MOVE THE CURSOR TO THE LEFT IN RELATION OF USED NEW LINES
				}
			}
			i++;
		}
		ret = read(fd, buf, MAX_READ);
	}
}

int	isometric_projection()
{
	int		i;
	int		i2;
	int		i3;
	char	*coordinate;
	int		x_pos;
	int		y_pos;
	int		depth;
	int		color;
}
