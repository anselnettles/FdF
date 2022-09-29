/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_01.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviholai <aviholai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 15:50:39 by aviholai          #+#    #+#             */
/*   Updated: 2022/09/29 14:06:42 by aviholai         ###   ########.fr       */
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

static int	open_read_projection(void *param)
{
	t_vars *v;
	v = (t_vars *)param;

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
				v->depth = depth_parser(crdnt);
				v->color = color_parser(crdnt, v->depth);
				mlx_pixel_put(v->mlx, v->win, v->x_pos, v->y_pos, v->color);
				v->x_pos += INCREMENT;
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

int	isometric_projection(void *param)
{
	int		i;
	int		i2;
	int		i3;
	char	*crdnt;
	t_vars	*v;

	v = (t_vars *)param;
	open_read_projection(param);
	while (v->ret)
	{
		v->buf[v->ret] = '\0';
		i = 0;
		i3 = 0;
		while (i < MAX_READ)
		{
			printf("\n| Buf: %d | Char: %c", i, v->buf[i]);
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
				v->depth = depth_parser(crdnt);
				v->color = color_parser(crdnt, v->depth);
				mlx_pixel_put(v->mlx, v->win, v->x_pos, v->y_pos, v->color);
				v->x_pos += (INCREMENT / 2); // AFTER EVERY PIXL GO ONE RIGHT
				v->y_pos += (INCREMENT / 2); // AFTER EVERY PIXL GO ONE DOWN
			}
			if (v->buf[i] == '\n')
			{
				i3++;
				v->x_pos = HALF_LENGTH - ((INCREMENT / 2) * i3);
				v->y_pos = START_POSITION + ((INCREMENT / 2) * i3);
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
