/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filsdefer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviholai <aviholai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 17:02:53 by aviholai          #+#    #+#             */
/*   Updated: 2022/09/27 12:17:18 by aviholai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILSDEFER_H
# define FILSDEFER_H

// Size definitions.
# define MAX_READ 500
# define START_POSITION 60
# define INCREMENT 40
# define PARALLEL_TRUE 1
# define PARALLEL_FALSE 0

// MAC Keyboard keys
# define ESC 53
# define RETURN 36
# define SHIFT 56

// Definitions for color constants.
# define NETTLE 0xAAD4B5
# define WHITE 0xFFFFFF

# define ORANGE '\033[0;33m'
# define GRAY '\033[0;37m'
# define RED '\033[1;31m¬'
# define GREEN '\033[1;32m'

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <string.h>
# include <math.h>
# include "mlx.h"

typedef struct	s_vars {
	void	*mlx;
	void	*win;
	ssize_t	newline_count;
}	t_vars;

// Error types
typedef enum e_error
{
	BAD_ARGS,
	OPEN_FAIL,
	READ_FAIL,
	INVALID_CHARS,
	CLOSE_FAIL,
	FILE_MAX,
	NO_PRINT,
}	t_error;

int		validate_file(const char *file, char *buf);
int		extract_file(const char *file, char *buf, int total_coordinates);
int		error(int errorcode);
int		ft_atoi(const char *str);
void	ft_putchar(char c);
size_t	ft_strlen(const char *s);
#endif
