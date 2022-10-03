/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_01.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviholai <aviholai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 15:50:39 by aviholai          #+#    #+#             */
/*   Updated: 2022/10/03 14:49:05 by aviholai         ###   ########.fr       */
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
	v->y_pos = START_POSITION;
	v->prev_y = v->y_pos;
	if (v->parallel_mode == PARALLEL_TRUE)
	{
		v->x_pos = START_POSITION;
		mlx_string_put(v->mlx, v->win, 60, 20, NIGHT,
			"[ P a r a l l e l ]  Projection Mode.");
	}
	if (v->parallel_mode == PARALLEL_FALSE)
	{
		v->x_pos = HALF_LENGTH;
		mlx_string_put(v->mlx, v->win, 60, 20, NIGHT,
			"[ I s o m e t r i c ]  Projection Mode.");
	}
	v->prev_x = v->x_pos;
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
	if (v->parallel_mode == PARALLEL_TRUE)
	{
		mlx_pixel_put(v->mlx, v->win, v->x_pos, v->y_pos, v->color);
		draw_line(v);
		v->prev_x = v->x_pos;
		v->prev_y = v->y_pos;
		v->x_pos += (INCREMENT);
	}
	if (v->parallel_mode == PARALLEL_FALSE)
	{
		v->y_pos += ((v->depth * ISOMETRIC_DEPTH) * -1);
		mlx_pixel_put(v->mlx, v->win, v->x_pos, v->y_pos, v->color);
		draw_line(v);
		v->prev_x = v->x_pos;
		v->prev_y = v->y_pos;
		v->x_pos += (ISOMETRIC_INCREMENT);
		v->y_pos += (ISOMETRIC_INCREMENT);
	}
	return (0);
}

static int	graphic_loop(t_vars *v)
{
	printf("\n| Buf: %d | Char: %c", v->i, v->buf[v->i]);
	if (v->buf[v->i] != ' ' && v->buf[v->i] != '\n'
		&& v->buf[v->i] != '\t' && v->buf[v->i])
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
		v->prev_x = -1;
		v->prev_y = -1;
		if (v->parallel_mode == PARALLEL_TRUE)
		{
			v->x_pos = START_POSITION;
			v->y_pos += INCREMENT;
		}
		if (v->parallel_mode == PARALLEL_FALSE)
		{
			v->x_pos = (int)(HALF_LENGTH - ((ISOMETRIC_INCREMENT) * v->nl));
			v->y_pos = (int)(START_POSITION + ((ISOMETRIC_INCREMENT) * v->nl));
		}
	}
	v->i++;
	return (0);
}

int	projection(t_vars *v)
{
	open_read_projection(v);
	while (v->ret)
	{
		v->buf[v->ret] = '\0';
		v->i = 0;
		v->nl = 0;
		while (v->i < MAX_READ)
		{
			if (graphic_loop(v) == -1)
				return (-1);
		}
		v->y_pos += INCREMENT;
		(v->ret = read(v->fd, v->buf, MAX_READ));
		if (v->ret < 0)
			return (READ_FAIL);
	}
	if (close(v->fd) == -1)
		return (error(CLOSE_FAIL));
	return (0);
}
