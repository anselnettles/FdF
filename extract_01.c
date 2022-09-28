/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_01.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviholai <aviholai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 15:50:39 by aviholai          #+#    #+#             */
/*   Updated: 2022/09/28 16:32:56 by aviholai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filsdefer.h"
#include <stdio.h>

static int	color_parser(char *coordinate, int depth)
{
	int		i;
	int		i2;
	char	*new_string;
	int		color;

	color = RED;
	i = 0;
	while (coordinate[i])
	{
		if (coordinate[i] == ',')
		{
			i++;
			i2 = 0;
			new_string = (char *)malloc(sizeof(char)*(ft_strlen(coordinate) + 1));
			while (coordinate[i])
			{
				new_string[i2] = coordinate[i];
				i++;
				i2++;
			}
			new_string[i2] = '\0';
			//FIGURE THIS OUT LATER.
			printf(" | HEX color: %s!", new_string);
			return (color = ft_atoi(new_string));
		}
		i++;
	}
	printf(" | Reg color.");
	if (depth < 5)
		return (color = 0xffbe00);
	else
		return (color = 0xffffff);
}

static int	depth_parser(char *coordinate)
{
	int		i;
	int		depth;
	char	*new_string;

	i = 0;
	new_string = (char *)malloc(sizeof(char)*(ft_strlen(coordinate) + 1));
	while (coordinate[i] != ',' && coordinate[i])
	{
		new_string[i] = coordinate[i];
		i++;
	}
	new_string[i] = '\0';
	printf(" | String: %s", new_string);
	depth = ft_atoi(new_string);
	printf(" | Atoi: %d", depth);
	return (depth);
}

/*
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
*/
int	isometric_projection(void *param)
{
	int		i;
	int		i2;
	int		i3;
	char	*coordinate;
	t_vars	*v;
	i = 0;

	v = (t_vars *)param;
	while (v->ret)
	{
		mlx_pixel_put(v->mlx, v->win, v->x_pos + 2, v->y_pos + i, NETTLE0);
		printf("\n| Buf: %d | Char: %c", i, v->buf[i]);
		i++;
		v->ret--;
	}

		//buf[vars.ret] = '\0';
	//	i = 0;
	//	while (i < MAX_READ)
	//	{
	//		printf("\n| Buf: %d | Char: %c", i, buf[i]);
	//		//IF BUF INDEX IS AT A COORDINATE:
	//		if (buf[i] != ' ' && buf[i] != '\n' && buf[i] != '\t' &&  buf[i])
	//		{
	//			coordinate = (char *)malloc(sizeof(char)*(ft_strlen(buf) + 1));
	//			i3 = 0;
	//			while (buf[i] != ' ' && buf[i] != '\n' && buf[i])
	//			{
	//				coordinate[i3] = buf[i];
	//				i++;
	//				i3++;
	//			}
	//			while (coordinate[i3])
	//			{
	//				coordinate[i3] = '\0';
	//				i3++;
	//			}
	//			depth = depth_parser(coordinate);
	//			color = color_parser(coordinate, depth);
	//			if (vars.parallel_mode == PARALLEL_TRUE)
	//				mlx_pixel_put(vars->mlx, vars->win, vars->x_pos, vars->y_pos, RED);
	//			if (vars.parallel_mode == PARALLEL_FALSE)
	//				isometric(x_pos, y_pos, color);
	//			x_pos += INCREMENT;
	//		}
	//		if (buf[i] == '\n')
	//		{
	//			total_newlines--;
	//			x_pos = START_POSITION;
	//			y_pos += INCREMENT;
	//			if (vars.parallel_mode == PARALLEL_FALSE)
	//			{
	//				// MOVE THE CURSOR BACK UP IN RELATION TO NUMBER OF X AXIS COORDINATES
	//				// MOVE THE CURSOR TO THE LEFT IN RELATION OF USED NEW LINES
	//			}
	//		}
	//		i++;
	//	}
	//	vars->y_pos += INCREMENT;
	//	vars.ret = read(fd, vars->buf, MAX_READ);
	//}
	return (0);
}
