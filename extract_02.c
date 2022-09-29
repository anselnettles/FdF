/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_02.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviholai <aviholai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 14:46:46 by aviholai          #+#    #+#             */
/*   Updated: 2022/09/29 14:47:43 by aviholai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filsdefer.h"
#include <stdio.h>

int	color_parser(char *coordinate, int depth)
{
	int		i;
	int		i2;
	char	*new_string;
	int		color;

	color = RED;
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

int	depth_parser(char *coordinate)
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
