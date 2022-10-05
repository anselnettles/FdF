/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_03.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviholai <aviholai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 11:54:01 by aviholai          #+#    #+#             */
/*   Updated: 2022/10/05 16:41:39 by aviholai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filsdefer.h"

/*
**	Prototype for the color variance during draw lines.
**	Still missing the necessary variables to make it truly adjustable.
**	For now, it toggles a different shade of color for every other pixel
**	during drawing the line phase.
*/

static int	shade(t_vars *v)
{
	int			shade;
	static int	toggle;

	if (toggle)
	{
		toggle = 0;
		shade = (v->color + 82);
		return (shade);
	}
	else
	{
		toggle = 1;
		return (v->color);
	}
}

void	draw_vertical(t_vars *v)
{	
	float	delta_x;
	float	delta_y;
	float	step;

	if (abs(v->x_pos - v->log_x[v->cl]) >= abs(v->y_pos - v->log_y[v->cl]))
		step = (float)abs(v->x_pos - v->log_x[v->cl]);
	else
		step = (float)abs(v->y_pos - v->log_y[v->cl]);
	delta_x = ((v->x_pos - v->log_x[v->cl]) / step);
	delta_y = ((v->y_pos - v->log_y[v->cl]) / step);
	v->li_x = v->log_x[v->cl];
	v->li_y = v->log_y[v->cl];
	while ((int)step-- >= 2)
	{
		v->li_x += delta_x;
		v->li_y += delta_y;
		mlx_pixel_put(v->mlx, v->win, (int)v->li_x, (int)v->li_y, shade(v));
	}
}

void	draw_horizontal(t_vars *v)
{
	float	delta_x;
	float	delta_y;
	float	step;

	if (abs(v->x_pos - v->prev_x) >= abs(v->y_pos - v->prev_y))
		step = (float)abs(v->x_pos - v->prev_x);
	else
		step = (float)abs(v->y_pos - v->prev_y);
	delta_x = ((v->x_pos - v->prev_x) / step);
	delta_y = ((v->y_pos - v->prev_y) / step);
	v->li_x = v->prev_x;
	v->li_y = v->prev_y;
	while ((int)step-- >= 2)
	{
		v->li_x += delta_x;
		v->li_y += delta_y;
		mlx_pixel_put(v->mlx, v->win, (int)v->li_x, (int)v->li_y, shade(v));
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
