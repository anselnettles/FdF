/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic_test.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviholai <aviholai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 16:29:41 by aviholai          #+#    #+#             */
/*   Updated: 2022/08/31 14:35:17 by aviholai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "mlx.h"
#define WHITE 0xFFFFFF
#define BROWN 0x800000
#define GREEN 0x008000
#define NETTLE 0xAAD4B5

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

static int	key(int key, void *param)
{
	int location_x;
	int location_y;
	location_x = 250;
	location_y = 250;
	ft_putchar('E');
	mlx_pixel_put(mlx_ptr, win_ptr, location_x, location_y, WHITE);
	location_x += 50;
	location_y += 50;
	return (0);
}

int	main(void)
{
	void	*mlx_ptr;
	void	*win_ptr;

	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, 1000, 1000,
			"aMIST the Nettles | Ansel's Magic Box");
	mlx_string_put(mlx_ptr, win_ptr, 40, 50, NETTLE,
		"Welcome to my magical graphic box.");
	mlx_string_put(mlx_ptr, win_ptr, 40, 80, NETTLE,
		"Gaze upon my beautiful art.");
	mlx_key_hook(win_ptr, key, (void *)0);
	mlx_loop(mlx_ptr);
	return (0);
}
