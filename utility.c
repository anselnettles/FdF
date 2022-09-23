/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviholai <aviholai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 16:29:43 by aviholai          #+#    #+#             */
/*   Updated: 2022/09/23 16:35:23 by aviholai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filsdefer.h"

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

/*
**	'PutChar()' (Put character) writes a single character at a time from
**	applied parameter 'c'.
*/

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

/*
**	'StrLen()' (String length) measures the length of the applied character
**	string parameter '*s'.
*/

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (s[len] != '\0')
		len++;
	return (len);
}

