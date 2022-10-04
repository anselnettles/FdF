/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_03.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviholai <aviholai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 11:54:01 by aviholai          #+#    #+#             */
/*   Updated: 2022/10/04 18:41:44 by aviholai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filsdefer.h"

static int	draw_vertical(t_vars *v)
{
	if (v->parallel_mode == PARALLEL_TRUE)
	{
		int i;
	
		i = 0;
		while (i != INCREMENT)
		{
			mlx_pixel_put(v->mlx, v->win, v->x_pos, v->y_pos - i, v->color);
			i++;
		}
	}
	if (v->parallel_mode == PARALLEL_FALSE)
	{
		float	x;
		float	y;
		int		i;
		float	dx;
		float	dy;
		float	step;

		i = 1;
		dx = (v->x_pos - v->log_x[v->column]);
		dy = (v->y_pos - v->log_y[v->column]);
		if (fabs(dx) >= fabs(dy))
			step = (float)fabs(dx);
		else
			step = (float)fabs(dy);
		dx = (dx / step);
		dy = (dy / step);
		x = v->log_x[v->column];
		y = v->log_y[v->column];
		while (i <= step)
		{
			x += dx;
			y += dy;
			mlx_pixel_put(v->mlx, v->win, (int)x, (int)y, v->color);
			i++;
		}
	}
	//	step = ((v->x_pos - v->prev_x) / ISOMETRIC_INCREMENT);
	//	while (v->log[v->i] < v->y_pos)
	//	{
	//		v->log[v->i]++;
	//		v->prev_x += step;
	//		mlx_pixel_put(v->mlx, v->win, v->prev_x, v->log[v->i], v->color);
	//	}
//
		//prevous y = edellisen rivin "topright" ja se depth calculaatio siitä,
		//eli edellisen rivin depth-arvot pitää ottaa talteen.
		//calculate bitch
	//WHEN OFF, TAKE THE LOCATION WHERE WE'RE AT AND DRAW IT TO THE LOCATION
	//OF A NEW VARIABLE WHERE YOU SAVED THE DEPTH INFORMATION FROM THE LAST ROW.
	//IF THERE WAS NO DEPTH INFORMATION, THAT SHOULD MEAN THE DIRECTION IS
	//STANDARD (topright?)
	return (0);
}

static int	draw_horizontal(t_vars *v)
{
	float	f_x_pos;
	float	f_y_pos;
	float	f_prev_x;
	float	f_prev_y;
	float	step;

	f_x_pos = v->x_pos;
	f_y_pos = v->y_pos;
	f_prev_x = v->prev_x;
	f_prev_y = v->prev_y;
	step = ((f_y_pos - f_prev_y) / ISOMETRIC_INCREMENT);
	while (f_prev_x < f_x_pos)
	{
		f_prev_x++;
		f_prev_y += step;
		v->prev_x = (int)f_prev_x;
		v->prev_y = (int)f_prev_y;
		mlx_pixel_put(v->mlx, v->win, v->prev_x, v->prev_y, v->color);
	}
	return(0);
}

int	draw_line(t_vars *v)
{
	if ((v->prev_x != -1) && (v->prev_y != -1))
		draw_horizontal(v);
	if (v->nl != 0)
		draw_vertical(v);
	return (0);
}
