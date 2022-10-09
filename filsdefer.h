/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filsdefer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviholai <aviholai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 17:02:53 by aviholai          #+#    #+#             */
/*   Updated: 2022/10/07 17:03:13 by aviholai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILSDEFER_H
# define FILSDEFER_H

// Size definitions.
# define MAX_READ 100000		// Maximum buffer size for READ()
# define WIDTH 1080				// Window resolution width
# define HEIGHT 920				// Window resolution height
# define START_POS 80			// Graph starting draw height (from top)
# define HALF_LENGTH 320		// Half of the resolution width (for Isometric)
# define INCREMENT 40			// The increment in-between pixel coordinates
# define ISOMETRIC_INCREMENT 30 // The increment when in Isometric Mode
# define ISOMETRIC_DEPTH 15		// Standard altitude setting for Z-axis
# define ISOMETRIC_TOGGLE 1		// ADJUST THIS for a different toggle option
# define PARALLEL_TRUE 1		// True statement for Parallel Mode
# define PARALLEL_FALSE 0		// False statement for Parallel Mode
# define NEW_LINE -1			// Used to neutralize variables

// MAC Keyboard keys
# define ESC 53
# define RETURN 36
# define SHIFT 56
# define TAB 48
# define A 0

// Definitions for color constants.
# define RED 0xCC0000
# define NETTLE 0xAAD4B5
# define NIGHT 0x152f37
# define DAWN 0x2b6173
# define ORANGE 0xE7C9B1
# define WHITE 0xdbdbdb
# define GRAY 0x828282

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <string.h>
# include <math.h>
# include "mlx.h"

typedef struct s_vars {
	void			*mlx;
	void			*win;
	char			*file;
	ssize_t			ret;
	char			*buf;
	int				column_check;
	int				read_newlines;
	int				read_numbers;
	int				read_columns;
	int				parallel_mode;
	int				i;
	int				cl;
	int				log_x[MAX_READ];
	int				log_y[MAX_READ];
	int				nl;
	int				y_pos;
	int				x_pos;
	int				prev_y;
	int				prev_x;
	float			li_x;
	float			li_y;
	int				color;
	int				color_i;
	int				color_i2;
	int				depth;
	int				fd;
	char			*coordinate;
	int				altitude;

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
	NO_NL,
}	t_error;

int		validate_file(const char *file, char *buf, t_vars *v);
int		extract_file(t_vars *v);
int		projection(t_vars *v);
int		draw_line(t_vars *v);
int		color_parser(char *coordinate, int depth, t_vars *v);
int		depth_parser(char *coordinate);
int		error(int errorcode);
int		ft_atoi(const char *str);
void	ft_putchar(char c);
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlen(const char *s);
#endif
