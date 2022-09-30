/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_03.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviholai <aviholai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 11:54:01 by aviholai          #+#    #+#             */
/*   Updated: 2022/09/30 14:50:10 by aviholai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filsdefer.h"
#include <stdio.h>

int	draw_line(t_vars *v)
{
	float	f_x_pos;
	float	f_y_pos;
	float	f_prev_x;
	float	f_prev_y;
	//float	amount;

	f_x_pos = v->x_pos;
	f_y_pos = v->y_pos;
	f_prev_x = v->prev_x;
	f_prev_y = v->prev_y;
	printf("\nPrev X = %d. Prev Y = %d. Now X = %d. Now Y = %d", v->prev_x, v->prev_y, v->x_pos, v->y_pos);
	while (f_prev_x <= f_x_pos)
	{
		f_prev_x++;
		f_prev_y += ((f_y_pos - f_prev_y) / INCREMENT);
		v->prev_x = (int)f_prev_x;
		v->prev_y = (int)f_prev_y;
		mlx_pixel_put(v->mlx, v->win, v->prev_x, v->prev_y, v->color);
	}

	return(0);
}
