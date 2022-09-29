/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filsdefer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviholai <aviholai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 17:02:53 by aviholai          #+#    #+#             */
/*   Updated: 2022/09/29 14:02:50 by aviholai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILSDEFER_H
# define FILSDEFER_H

// Size definitions.
# define MAX_READ 500
# define START_POSITION 60
# define HALF_LENGTH 320
# define INCREMENT 40
# define PARALLEL_TRUE 1
# define PARALLEL_FALSE 0

// MAC Keyboard keys
# define ESC 53
# define RETURN 36
# define SHIFT 56
# define TAB 48

// Definitions for color constants.
# define RED 0xCC0000
# define NETTLE0 0xAAD4B5
# define NIGHT 0x204855
# define ORANGE 0xE7C9B1
# define WHITE 0xFFFFFF

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <string.h>
# include <math.h>
# include "mlx.h"

typedef struct	s_vars {
	void			*mlx;
	void			*win;
	char			*file;
	ssize_t			ret;
	char			*buf;
	int				total_newlines;
	ssize_t			newline_count;
	int				parallel_mode;
	int				y_pos;
	int				x_pos;
	int				color;
	int				depth;
	int				fd;
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
int		extract_file(char *file, char *buf, int total_coordinates);
int		parallel_projection(void *param);
int		isometric_projection(void *param);
int		error(int errorcode);
int		ft_atoi(const char *str);
void	ft_putchar(char c);
size_t	ft_strlen(const char *s);
#endif
