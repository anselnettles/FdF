/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic_test.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviholai <aviholai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 16:29:41 by aviholai          #+#    #+#             */
/*   Updated: 2022/09/05 15:12:27 by aviholai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "mlx.h"
#define WHITE 0xFFFFFF
#define BROWN 0x800000
#define GREEN 0x008000
#define NETTLE 0xAAD4B5

typedef struct	s_vars {
	void	*mlx;
	void	*win;
	int	x;
	int	y;
}	t_vars;

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

int	key(int key, t_vars *vars)
{
	ft_putchar('E');
	mlx_pixel_put(vars->mlx, vars->win, vars->x, vars->y, WHITE);
	vars->y += 1;
	vars->x += 1;
	return (0);
}

int	main(void)
{
	t_vars	vars;
	vars.y = 250;
	vars.x = 250;

	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, 1000, 1000,
			"aMIST the Nettles | Ansel's Magic Box");
	mlx_string_put(vars.mlx, vars.win, 40, 50, NETTLE,
		"Welcome to my magical graphic box.");
	mlx_string_put(vars.mlx, vars.win, 40, 80, NETTLE,
		"Gaze upon the beautiful line with every key press.");
	mlx_key_hook(vars.win, key, &vars);
	mlx_loop(vars.mlx);
	return (0);
}
