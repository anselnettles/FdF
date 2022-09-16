/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_extract.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviholai <aviholai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 12:04:53 by aviholai          #+#    #+#             */
/*   Updated: 2022/09/16 17:00:02 by aviholai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filsdefer.h"
#include <stdio.h>

#define MAXIMUM 9223372036854775807

/*
**	'AtoI()' (ASCII to integer) converts the applied character number
**	string into an integer value.
**	When it comes to overly long number strings, for the function to behave the
**	same way as the original 'atoi()', we have defined a number maximum.
**	The first condition  ascertains if the first character is
**	a white space, hor. tab, newline, vert. tab, form feed or carriage return
**	and increments to the next character, until not the case.
**	The second condition checks whether the number begins with a
**	minus sign and applies the integer 'if_negative' to (-1), if so.
**	The third condition skips ahead of the string if more minus or
**	plus signs are found.
**	Finally, the fourth condition applies the found digit numbers
**	into integer 'result' one digit at a time while incrementing through
**	the string. In case the number is larger than the defined 'MAXIMUM' it will
**	be returned the way the original 'atoi()' does.
**	The result is then returned after being factored with the integer
**	of 'if_negative'.
*/

int	ft_atoi(const char *str)
{
	unsigned long long	result;
	int					if_negative;

	result = 0;
	if_negative = 1;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-')
		if_negative = -1;
	if (*str == '-' || *str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + (unsigned long long)*str - '0';
		str++;
		if (result >= MAXIMUM && if_negative == 1)
			return (-1);
		else if (result > MAXIMUM && if_negative == -1)
			return (0);
	}
	return ((int)result * if_negative);
}

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

//int	keypress(int key, void *param)
//{
//	t_vars	*vars;
//
//	vars = (t_vars *)param;
//	if (key == 13)
//	{	
//		vars->y -= 1;
//		ft_putchar('W');
//		mlx_pixel_put(vars->mlx, vars->win, vars->x, vars->y, WHITE);
//	}
//	if (key == 0)
//	{
//		vars->x -= 1;
//		ft_putchar('A');
//		mlx_pixel_put(vars->mlx, vars->win, vars->x, vars->y, WHITE);
//	}
//	if (key == 1)
//	{
//		vars->y += 1;
//		ft_putchar('S');
//		mlx_pixel_put(vars->mlx, vars->win, vars->x, vars->y, WHITE);
//	}
//	if (key == 2)
//	{
//		vars->x += 1;
//		ft_putchar('D');
//		mlx_pixel_put(vars->mlx, vars->win, vars->x, vars->y, WHITE);
//	}
//	return (0);
//}

int	graphic(int x, int y, char *buf)
{
	t_vars	vars;
	vars.y = y;
	vars.x = x;

	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, 1000, 1000,
			"aMIST the Nettles | Ansel's Magic Box");
	mlx_string_put(vars.mlx, vars.win, 40, 50, NETTLE,
		"Welcome to my magical graphic box.");
//	mlx_string_put(vars.mlx, vars.win, 40, 80, NETTLE,
//		"Gaze upon the beautiful line with every key press.");
//	mlx_key_hook(vars.win, keypress, (void *)&vars);
	mlx_string_put(vars.mlx, vars.win, x, y, NETTLE,
			"J");
	mlx_loop(vars.mlx);
	return (0);
}


int	extract_file(const char *file, char *buf, int total_coordinates)
{
	int		fd;
	ssize_t	ret;
	int		seize;

	printf("\n\nWelcome to extract_file(). \nSo, total_coordinates is %d\n",
			total_coordinates);
	fd = open(file, O_RDONLY);
	ret = read(fd, buf, MAX_READ);
	while (ret)
	{
		buf[ret] = '\0';
		printf("|Buf0:%c", buf[0]);
		if (buf[0] >= '0' && buf[0] <= '9')
			seize = ft_atoi(&buf[0]);
		printf("|Buf1:%c", buf[1]);
		printf("|Buf2:%c", buf[2]);
		printf("|Buf3:%c", buf[3]);
		printf("|Buf4:%c", buf[4]);
		printf("|Buf5:%c", buf[5]);
		printf("|Buf6:%c", buf[6]);
		printf("|Buf7:%c", buf[7]);
		printf("|Buf8:%c", buf[8]);
		printf("|Buf9:%c", buf[9]);
		ret = read(fd, buf, MAX_READ);
	printf("\nPlease, return the integer coordinate to me: %d\n\n", seize);
	graphic(250, 250, &buf[0]);
	}
	return(0);
}
