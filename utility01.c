/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility01.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviholai <aviholai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 16:27:48 by aviholai          #+#    #+#             */
/*   Updated: 2022/09/30 16:31:05 by aviholai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filsdefer.h"

/*
**	'Strcpy()' (String copy) makes a copy of the second parameter string
**	(char *src) into the first parameter (char *dst) and returns 'dst'..
*/

char	*ft_strcpy(char *dst, const char *src)
{
	size_t	i;

	i = 0;
	while (src[i] != '\0')
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}
