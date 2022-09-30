/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviholai <aviholai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 12:04:53 by aviholai          #+#    #+#             */
/*   Updated: 2022/09/30 11:04:25 by aviholai         ###   ########.fr       */
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

static int	initialization(t_vars *v)
{
	v->win = mlx_new_window(v->mlx, 640, 480,
			"Filsdefer | github.com/anselnettles");
	mlx_string_put(v->mlx, v->win, 30, 20, NETTLE,
		"Filsdefer |  \\fil ade fer\\ | wireframe");
	mlx_string_put(v->mlx, v->win, 60, 45, NIGHT,
		"A skeletal three-dimensional model in which");
	mlx_string_put(v->mlx, v->win, 60, 65, NIGHT,
		"only lines and vertices are represented.");
	mlx_string_put(v->mlx, v->win, 30, 120, ORANGE,
		"Press TAB to toggle projection.");
	mlx_string_put(v->mlx, v->win, 30, 160, ORANGE,
		"Press ESC to quit.");
	mlx_string_put(v->mlx, v->win, 240, 425, NETTLE,
		"Ansel Nettles | github.com/anselnettles");
	mlx_string_put(v->mlx, v->win, 240, 445, NIGHT,
		"\" C o d e - ' n - S w o r d \"");
	return (0);
}

int	extract_file(char *file, char *buf, t_vars *v)
{
	//printf("\n\nWelcome to extract_file(). \nSo, total_newlines is %d\n",
	//		total_newlines);
	//v.total_newlines = total_newlines;
	v->file = file;
	v->buf = buf;
	//v.fd = open(file, O_RDONLY);
	//v.ret = read(v.fd, v.buf, MAX_READ);
	v->mlx = mlx_init();
	if (initialization(v) != 0)
		return (-1);
	v->parallel_mode = PARALLEL_FALSE;
	mlx_key_hook(v->win, keypress, (void *)v);
	mlx_loop(v->mlx);
	return (0);
}
