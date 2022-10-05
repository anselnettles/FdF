/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_01.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviholai <aviholai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 15:50:39 by aviholai          #+#    #+#             */
/*   Updated: 2022/10/05 14:36:31 by aviholai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filsdefer.h"
#include <stdio.h>

static int	open_read_projection(t_vars *v)
{
	v->fd = open(v->file, O_RDONLY);
	if (v->fd == -1)
		return (error(OPEN_FAIL));
	v->ret = read(v->fd, v->buf, MAX_READ);
	if (v->ret == -1)
		return (error(READ_FAIL));
	if (v->parallel_mode == PARALLEL_TRUE)
	{
		v->x_pos = START_POSITION;
		mlx_string_put(v->mlx, v->win, 60, 20, DAWN,
			"[ P a r a l l e l ]  Projection Mode.");
	}
	if (v->parallel_mode == PARALLEL_FALSE)
	{
		v->x_pos = HALF_LENGTH;
		mlx_string_put(v->mlx, v->win, 60, 20, DAWN,
			"[ I s o m e t r i c ]  Projection Mode.");
	}
	return (0);
}

char	*write_coordinate(t_vars *v)
{
	char	*coordinate;
	int		i2;

	coordinate = (char *)malloc(sizeof(char) * (ft_strlen(v->buf) + 1));
	if (coordinate == NULL)
		return (NULL);
	i2 = 0;
	while (v->buf[v->i] != ' ' && v->buf[v->i] != '\n' && v->buf[v->i])
	{
		coordinate[i2] = v->buf[v->i];
		v->i++;
		i2++;
	}
	while (coordinate[i2])
	{
		coordinate[i2] = '\0';
		i2++;
	}
	return (coordinate);
}

int	draw_pixel(t_vars *v)
{
	v->depth = depth_parser(v->coordinate);
	v->color = color_parser(v->coordinate, v->depth);
	if (v->parallel_mode == PARALLEL_FALSE)
		v->y_pos += ((v->depth * ISOMETRIC_DEPTH) * -1);
	mlx_pixel_put(v->mlx, v->win, v->x_pos, v->y_pos, v->color);
	draw_line(v);
	v->log_x[v->cl] = v->x_pos;
	v->log_y[v->cl] = v->y_pos;
	printf(" | Log_Y[i] (height): %d | Log_X[i] (width): %d", v->log_y[v->cl], v->log_x[v->cl]);
	v->prev_x = v->x_pos;
	v->prev_y = v->y_pos;
	if (v->parallel_mode == PARALLEL_TRUE)
		v->x_pos += (INCREMENT);
	else if (v->parallel_mode == PARALLEL_FALSE)
	{
		v->x_pos += (ISOMETRIC_INCREMENT);
		v->y_pos += (ISOMETRIC_INCREMENT + (v->depth * ISOMETRIC_DEPTH));
	}
	v->cl++;
	return (0);
}

static int	graphic_loop(t_vars *v)
{
	while (v->i < MAX_READ)
	{
		printf("\n| Buf: %d | Char: %c", v->i, v->buf[v->i]);
		if ((v->buf[v->i] != ' ' && v->buf[v->i] != '\n') && v->buf[v->i])
		{
			v->coordinate = write_coordinate(v);
			if (v->coordinate == NULL)
				return (-1);
			if (draw_pixel(v) == -1)
				return (-1);
		}
		if (v->buf[v->i] == '\n')
		{
			v->nl++;
			v->cl = 0;
			v->prev_x = NEW_LINE;
			v->prev_y = NEW_LINE;
			if (v->parallel_mode == PARALLEL_TRUE)
			{
				v->x_pos = START_POSITION;
				v->y_pos += INCREMENT;
			}
			else if (v->parallel_mode == PARALLEL_FALSE)
			{
				v->x_pos = (int)(HALF_LENGTH - ((ISOMETRIC_INCREMENT) * v->nl));
				v->y_pos = (int)(START_POSITION + ((ISOMETRIC_INCREMENT) * v->nl));
			}
		}
		v->i++;
	}
	return (0);
}

int	projection(t_vars *v)
{
	v->i = 0;
	v->nl = 0;
	v->cl = 0;
	v->y_pos = START_POSITION;
	v->prev_x = NEW_LINE;
	v->prev_y = NEW_LINE;
	open_read_projection(v);
	//v->i = 0;
	//v->nl = 0;
	while (v->ret)
	{
		v->buf[v->ret] = '\0';
		//v->i = 0;
		//v->nl = 0;
		if (graphic_loop(v) == -1)
			return (-1);
		//v->y_pos += INCREMENT;
		v->ret = read(v->fd, v->buf, MAX_READ);
		if (v->ret < 0)
			return (READ_FAIL);
	}
	if (close(v->fd) == -1)
		return (error(CLOSE_FAIL));
	return (0);
}
