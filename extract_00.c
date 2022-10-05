/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviholai <aviholai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 12:04:53 by aviholai          #+#    #+#             */
/*   Updated: 2022/10/05 16:14:59 by aviholai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filsdefer.h"
#include <stdio.h>

/*
**	Function 'keypress()' is alert and awaiting for a press of a key and
**	manipulates the 'MiniLibX' graphic window accordingly.
**	MAC key 'TAB' toggles between "parallel" and "isometric" views (see
**	'extract_01.c' for the projections).
**	MAC key 'ESC' shuts down the graphic window and exits the program.
**	The function stays awake and observant for it's connected through the
**	'MLX' keyhook function. See 'mlx_key_hook()' in 'extract_file()', below.
*/

int	keypress(int key, void *param)
{
	t_vars	*v;

	v = (t_vars *)param;
	if (key == TAB)
	{
		mlx_clear_window(v->mlx, v->win);
		if (v->parallel_mode == PARALLEL_FALSE)
			v->parallel_mode = PARALLEL_TRUE;
		else if (v->parallel_mode == PARALLEL_TRUE)
			v->parallel_mode = PARALLEL_FALSE;
		projection(v);
	}
	if (key == ESC)
	{
		mlx_destroy_window(v->mlx, v->win);
		exit (0);
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
	mlx_string_put(v->mlx, v->win, 240, 425, NETTLE,
		"Ansel Nettles | github.com/anselnettles");
	mlx_string_put(v->mlx, v->win, 240, 445, DAWN,
		"\" C o d e - ' n - S w o r d \"");
	v->parallel_mode = PARALLEL_FALSE;
}

int	extract_file(t_vars *v)
{
	v->mlx = mlx_init();
	initialization(v);
	mlx_key_hook(v->win, keypress, (void *)v);
	mlx_loop(v->mlx);
	return (0);
}
