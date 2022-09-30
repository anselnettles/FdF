/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_03.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviholai <aviholai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 11:54:01 by aviholai          #+#    #+#             */
/*   Updated: 2022/09/30 17:05:23 by aviholai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filsdefer.h"

static int	draw_vertical()
{
	return (0);
}

static int	draw_horizontal(t_vars *v)
{
	float	f_x_pos;
	float	f_y_pos;
	float	f_prev_x;
	float	f_prev_y;
	float	step;
	double	distance;

	f_x_pos = v->x_pos;
	f_y_pos = v->y_pos;
	f_prev_x = v->prev_x;
	f_prev_y = v->prev_y;
	distance = INCREMENT / 1.5;
	step = ((f_y_pos - f_prev_y) / (float)distance);
	while (f_prev_x <= f_x_pos)
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
	draw_horizontal(v);
	draw_vertical();
	return (0);
}
