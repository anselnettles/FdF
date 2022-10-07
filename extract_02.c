/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_02.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviholai <aviholai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 14:46:46 by aviholai          #+#    #+#             */
/*   Updated: 2022/10/07 11:49:22 by aviholai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filsdefer.h"

/*
** A very bare color picker for different integer depth values.
** For future, this could be developed further by going through the different
** depth values before we're at the pixel drawing phase and comparing the
** values and coming up with a spectrum scale and drawing each depth level
** in unique color.
*/

static int	regular_color(int depth)
{
	int	color;

	if (depth < 0)
		return (color = NIGHT);
	else if (depth == 0)
		return (color = DAWN);
	else if (depth >= 1 && depth <= 5)
		return (color = NETTLE);
	else if (depth >= 6 && depth <= 9)
		return (color = ORANGE);
	else if (depth > 9)
		return (color = WHITE);
	else
		return (color = RED);
}

/*
**	Missing the HEX color code adjuster.
*/

int	color_parser(char *coordinate, int depth, t_vars *v)
{
	int		color;

	v->color_i = 0;
	while (coordinate[v->color_i])
	{
		if (coordinate[v->color_i] == ',')
			return (color = RED);
		v->color_i++;
	}
	return (color = regular_color(depth));
}

int	depth_parser(char *coordinate)
{
	int		i;
	int		depth;
	char	*new_string;

	i = 0;
	new_string = (char *)malloc(sizeof(char) * (ft_strlen(coordinate) + 1));
	if (new_string == NULL)
		return (-1);
	while (coordinate[i] != ',' && coordinate[i])
	{
		new_string[i] = coordinate[i];
		i++;
	}
	new_string[i] = '\0';
	depth = ft_atoi(new_string);
	free(new_string);
	return (depth);
}
