/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_01.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviholai <aviholai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 15:50:39 by aviholai          #+#    #+#             */
/*   Updated: 2022/09/29 16:57:20 by aviholai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filsdefer.h"
#include <stdio.h>

static int	open_read_projection(t_vars *v)
{
	if ((v->fd = open(v->file, O_RDONLY)) == -1)
		return (error(OPEN_FAIL));
	if ((v->ret = read(v->fd, v->buf, MAX_READ)) == -1)
		return (error(READ_FAIL));
	v->y_pos = START_POSITION;
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
	return (0);
}
/*
int	parallel_projection(void *param)
{
	int		i;
	int		i2;
	char	*crdnt;
	t_vars	*v;

	v = (t_vars *)param;
	open_read_projection(param);
	while (v->ret)
	{
		v->buf[v->ret] = '\0';
		i = 0;
		while (i < MAX_READ)
		{
			printf("\n| Buf: %d | Char: %c", i, v->buf[i]);
			//IF BUF INDEX IS AT A COORDINATE:
			if (v->buf[i] != ' ' && v->buf[i] != '\n'
					&& v->buf[i] != '\t' && v->buf[i])
			{
				crdnt = (char *)malloc(sizeof(char)*(ft_strlen(v->buf) + 1));
				i2 = 0;
				while (v->buf[i] != ' ' && v->buf[i] != '\n' && v->buf[i])
				{
					crdnt[i2] = v->buf[i];
					i++;
					i2++;
				}
				while (crdnt[i2])
				{
					crdnt[i2] = '\0';
					i2++;
				}
				if (draw_pixel(param, crdnt) == -1)
					return (-1);
			}
			if (v->buf[i] == '\n')
			{
			//	v->total_newlines--;
				v->x_pos = START_POSITION;
				v->y_pos += INCREMENT;
			}
			i++;
		}
		v->y_pos += INCREMENT;
		v->ret = read(v->fd, v->buf, MAX_READ);
	}
	if (close(v->fd) == -1)
		return(error(CLOSE_FAIL));
	return (0);
}
*/

char	*write_coordinate(t_vars *v)
{
	char	*coordinate;
	int		i2;

	coordinate = (char *)malloc(sizeof(char)*(ft_strlen(v->buf) + 1));
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


int	draw_pixel(t_vars *v, char *coordinate)
{
	v->depth = depth_parser(coordinate);
	v->color = color_parser(coordinate, v->depth);
	if (v->parallel_mode == PARALLEL_TRUE)
	{
		mlx_pixel_put(v->mlx, v->win, v->x_pos, v->y_pos, v->color);
		v->x_pos += (INCREMENT);
	}
	if (v->parallel_mode == PARALLEL_FALSE)
	{
		mlx_pixel_put(v->mlx, v->win, v->x_pos, (v->y_pos + ((v->depth * 10) * -1)), v->color);
		v->x_pos += (INCREMENT / 1.5);
		v->y_pos += (INCREMENT / 1.5);
	}
	return (0);
}

static int	graphic_loop(t_vars *v)
{
	char	*coordinate;

	printf("\n| Buf: %d | Char: %c", v->i, v->buf[v->i]);
	if (v->buf[v->i] != ' ' && v->buf[v->i] != '\n'
			&& v->buf[v->i] != '\t' && v->buf[v->i])
	{
		if ((coordinate = write_coordinate(v)) == NULL)
			return (-1);
		if ((draw_pixel(v, coordinate)) == -1)
			return (-1);
	}
	if (v->buf[v->i] == '\n')
	{
		v->nl++;
		if (v->parallel_mode == PARALLEL_TRUE)
		{
			v->x_pos = START_POSITION;
			v->y_pos += INCREMENT;
		}
		if (v->parallel_mode == PARALLEL_FALSE)
		{
			v->x_pos = HALF_LENGTH - ((INCREMENT / 1.5) * v->nl);
			v->y_pos = START_POSITION + ((INCREMENT / 1.5) * v->nl);
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
		v->ret = read(v->fd, v->buf, MAX_READ);
	}
	if (close(v->fd) == -1)
		return(error(CLOSE_FAIL));
	return (0);
}
