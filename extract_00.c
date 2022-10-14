/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviholai <aviholai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 12:04:53 by aviholai          #+#    #+#             */
/*   Updated: 2022/10/14 15:58:32 by aviholai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filsdefer.h"
#include "stdio.h"

/*
**	Function 'keypress()' is alert and awaiting for a press of a key and
**	manipulates the 'MiniLibX' graphic window accordingly.
**	MAC key 'TAB' toggles between "parallel" and "isometric" views (see
**	'extract_01.c' for the projections).
**	MAC key 'ESC' shuts down the graphic window and exits the program.
**	The function stays awake and observant for it's connected through the
**	'MLX' keyhook function. See 'mlx_key_hook()' in 'extract_file()', below.
*/

int		keypress(int key, void *param)
{
	t_vars	*v;

	v = (t_vars *)param;
	if (key)
	{
		if (key == TAB)
		{
			if (v->parallel_mode == PARALLEL_FALSE)
				v->parallel_mode = PARALLEL_TRUE;
			else if (v->parallel_mode == PARALLEL_TRUE)
				v->parallel_mode = PARALLEL_FALSE;
		}
		if (key == A)
		{
			if (v->altitude == ISOMETRIC_DEPTH)
				v->altitude = ISOMETRIC_TOGGLE;
			else
				v->altitude = ISOMETRIC_DEPTH;
		}
		if (key == PLUSA || key == PLUSB)
		{
			v->increment *= 1.10;
			v->isometric_increment *= 1.10;
		}
		if (key == MINUSA || key == MINUSB)
		{
			v->increment *= 0.90;
			v->isometric_increment *= 0.90;
		}
		if (v->increment < 40)
		{
			if (key == UP || key == NUM_UP)
			v->y_start_pos += 20;
			if (key == DOWN || key == NUM_DOWN)
			v->y_start_pos -= 20;
			if (key == LEFT || key == NUM_LEFT)
			v->x_start_pos += 20;
			if (key == RIGHT || key == NUM_RIGHT)
			v->x_start_pos -= 20;
		}
		else
		{
			if (key == UP || key == NUM_UP)
			v->y_start_pos += 60;
			if (key == DOWN || key == NUM_DOWN)
			v->y_start_pos -= 60;
			if (key == LEFT || key == NUM_LEFT)
			v->x_start_pos += 60;
			if (key == RIGHT || key == NUM_RIGHT)
			v->x_start_pos -= 60;
		}
		if (key == ESC)
		{
			mlx_destroy_window(v->mlx, v->win);
			exit (0);
		}
		mlx_clear_window(v->mlx, v->win);
		projection(v);
	}
	return (0);
}

void	initialization(t_vars *v)
{
	v->win = mlx_new_window(v->mlx, WIDTH, HEIGHT,
			"Filsdefer | github.com/anselnettles");
	mlx_string_put(v->mlx, v->win, 30, 20, NETTLE,
		"Filsdefer |  \\fil ade fer\\ | wireframe");
	mlx_string_put(v->mlx, v->win, 60, 45, DAWN,
		"A skeletal three-dimensional model in which");
	mlx_string_put(v->mlx, v->win, 60, 65, DAWN,
		"only lines and vertices are represented.");
	mlx_string_put(v->mlx, v->win, 30, 120, ORANGE,
		"Press TAB to toggle projection.");
	mlx_string_put(v->mlx, v->win, 30, 160, ORANGE,
		"Press ESC to quit.");
	mlx_string_put(v->mlx, v->win, 30, 200, ORANGE,
		"Press A to toggle isometric altitude.");
	mlx_string_put(v->mlx, v->win, 30, 240, ORANGE,
		"Press + to zoom in");
	mlx_string_put(v->mlx, v->win, 30, 280, ORANGE,
		"Press - to zoom out");
	mlx_string_put(v->mlx, v->win, WIDTH - 440, HEIGHT - 65, NETTLE,
		"Ansel Nettles | github.com/anselnettles");
	mlx_string_put(v->mlx, v->win, WIDTH - 440, HEIGHT - 45, DAWN,
		"\" C o d e - ' n - S w o r d \"");
	v->parallel_mode = PARALLEL_FALSE;
	v->altitude = ISOMETRIC_DEPTH;
	v->x_start_pos = START_POS;
	v->y_start_pos = START_POS;
//	v->half_length = START_POS;
	v->increment = INCREMENT;
	v->isometric_increment = ISOMETRIC_INCREMENT;
}

int	extract_file(t_vars *v)
{
	v->mlx = mlx_init();
	initialization(v);
	mlx_key_hook(v->win, keypress, (void *)v);
	mlx_loop(v->mlx);
	return (0);
}
