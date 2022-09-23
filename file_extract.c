/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_extract.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviholai <aviholai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 12:04:53 by aviholai          #+#    #+#             */
/*   Updated: 2022/09/23 16:12:08 by aviholai         ###   ########.fr       */
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

//int	graphic(int x, int y, int seize)
//{
//	t_vars	vars;
//	vars.y = y;
//	vars.x = x;
//
//	vars.mlx = mlx_init();
//	vars.win = mlx_new_window(vars.mlx, 1000, 1000,
//			"aMIST the Nettles | Ansel's Magic Box");
//	mlx_string_put(vars.mlx, vars.win, 40, 50, NETTLE,
//		"Welcome to my magical graphic box.");
//	mlx_string_put(vars.mlx, vars.win, 40, 80, NETTLE,
//		"Gaze upon the beautiful line with every key press.");
//	mlx_key_hook(vars.win, keypress, (void *)&vars);
//	mlx_loop(vars.mlx);
//	return (0);
//}

/*static int	buf_relocate(int i, char *buf)
{
	while (buf[i] != ' ' && buf[i] != ',' && buf[i] != '\n' && buf[i])
		i++
*/

static int	color_parser(char *coordinate, int depth)
{
	int		i;
	int		i2;
	char	*new_string;
	int		color;

	color = 0xcc0000;
	i = 0;
	while (coordinate[i])
	{
		if (coordinate[i] == ',')
		{
			i++;
			i2 = 0;
			new_string = (char *)malloc(sizeof(char)*(ft_strlen(coordinate) + 1));
			while (coordinate[i])
			{
				new_string[i2] = coordinate[i];
				i++;
				i2++;
			}
			new_string[i2] = '\0';
			//FIGURE THIS OUT LATER.
			printf(" | HEX color: %s!", new_string);
			return (color = ft_atoi(new_string));
		}
		i++;
	}
	printf(" | Reg color.");
	if (depth < 5)
		return (color = 0xffbe00);
	else
		return (color = 0xffffff);
}

static int	depth_parser(char *coordinate)
{
	int		i;
	int		depth;
	char	*new_string;

	i = 0;
	new_string = (char *)malloc(sizeof(char)*(ft_strlen(coordinate) + 1));
	while (coordinate[i] != ',' && coordinate[i])
	{
		new_string[i] = coordinate[i];
		i++;
	}
	new_string[i] = '\0';
	printf(" | String: %s", new_string);
	depth = ft_atoi(new_string);
	printf(" | Atoi: %d", depth);
	return (depth);
}

int	extract_file(const char *file, char *buf, int total_newlines)
{
	int		fd;
	ssize_t	ret;
	t_vars	vars;
	int		i;
	int		i2;
	int		i3;
	char	*coordinate;
	int		x_pos;
	int		y_pos;
	int		depth;
	int		color;


	printf("\n\nWelcome to extract_file(). \nSo, total_newlines is %d\n",
			total_newlines);
	fd = open(file, O_RDONLY);
	ret = read(fd, buf, MAX_READ);
	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, 640, 480,
			"aMIST the Nettles | Ansel's Magic Box");
	mlx_string_put(vars.mlx, vars.win, 30, 20, NETTLE,
		"Welcome to my magical graphic box.");
	x_pos = START_POSITION;
	y_pos = START_POSITION;
	color = 0;
	while (ret)
	{
		buf[ret] = '\0';
		i = 0;
		while (i < MAX_READ)
		{
			printf("\n| Buf: %d | Char: %c", i, buf[i]);
			//IF BUF INDEX IS AT A COORDINATE:
			if (buf[i] != ' ' && buf[i] != '\n' && buf[i] != '\t' &&  buf[i])
			{
				coordinate = (char *)malloc(sizeof(char)*(ft_strlen(buf) + 1));
				i3 = 0;
				while (buf[i] != ' ' && buf[i] != '\n' && buf[i])
				{
					coordinate[i3] = buf[i];
					i++;
					i3++;
				}
				while (coordinate[i3])
				{
					coordinate[i3] = '\0';
					i3++;
				}
				depth = depth_parser(coordinate);
				color = color_parser(coordinate, depth);
				mlx_pixel_put(vars.mlx, vars.win, x_pos, y_pos, color);
				x_pos += INCREMENT;
			}
				//if (buf[i + 1] != '\n' && buf[i + 2] != '\n')
				//{
				//	i2 = 1;
				//	while (i2 <= (INCREMENT - 1))
				//	{
				//		mlx_pixel_put(vars.mlx, vars.win, x_pos + i2, y_pos, color);
				//		i2++;
				//	}
				//}
				//if (total_newlines > 1)
				//	i2 = 1;
				//	while (i2 <= (INCREMENT - 1))
				//	{
				//		mlx_pixel_put(vars.mlx, vars.win, x_pos, y_pos + i2, color);
				//		i2++;
				//	}
		//	}
			if (buf[i] == '\n')
			{
				total_newlines--;
				x_pos = START_POSITION;
				y_pos += INCREMENT;
			}
			i++;
		}
		ret = read(fd, buf, MAX_READ);
	}
	mlx_loop(vars.mlx);
	return(0);
}
