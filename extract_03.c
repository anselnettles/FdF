/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_03.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviholai <aviholai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 11:54:01 by aviholai          #+#    #+#             */
/*   Updated: 2022/10/05 14:34:26 by aviholai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filsdefer.h"

void	draw_vertical(t_vars *v)
{	
		float	line_x;
		float	line_y;
		float	delta_x;
		float	delta_y;
		float	step;

		if (abs(v->x_pos - v->log_x[v->cl]) >= abs(v->y_pos - v->log_y[v->cl]))
			step = (float)abs(v->x_pos - v->log_x[v->cl]);
		else
			step = (float)abs(v->y_pos - v->log_y[v->cl]);
		delta_x = ((v->x_pos - v->log_x[v->cl]) / step);
		delta_y = ((v->y_pos - v->log_y[v->cl]) / step);
		line_x = v->log_x[v->cl];
		line_y = v->log_y[v->cl];
		while ((int)step-- >= 2)
		{
			line_x += delta_x;
			line_y += delta_y;
			mlx_pixel_put(v->mlx, v->win, (int)line_x, (int)line_y, v->color);
		}
}

void	draw_horizontal(t_vars *v)
{
		float	line_x;
		float	line_y;
		float	delta_x;
		float	delta_y;
		float	step;

		if (abs(v->x_pos - v->prev_x) >= abs(v->y_pos - v->prev_y))
			step = (float)abs(v->x_pos - v->prev_x);
		else
			step = (float)abs(v->y_pos - v->prev_y);
		delta_x = ((v->x_pos - v->prev_x) / step);
		delta_y = ((v->y_pos - v->prev_y) / step);
		line_x = v->prev_x;
		line_y = v->prev_y;
		while ((int)step-- >= 2)
		{
			line_x += delta_x;
			line_y += delta_y;
			mlx_pixel_put(v->mlx, v->win, (int)line_x, (int)line_y, v->color);
		}

}

int	draw_line(t_vars *v)
{
	if ((v->cl != 0 || v->nl != 0))
	{
		if ((v->prev_x != NEW_LINE) || (v->prev_y != NEW_LINE))
			draw_horizontal(v);
		if (v->nl != 0)
		draw_vertical(v);
	}
	return (0);
}
