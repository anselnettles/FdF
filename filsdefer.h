/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filsdefer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviholai <aviholai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 17:02:53 by aviholai          #+#    #+#             */
/*   Updated: 2022/09/22 15:33:53 by aviholai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILSDEFER_H
# define FILSDEFER_H

// Size definitions.
# define MAX_READ 10
# define START_POSITION 60
# define INCREMENT 40

// Definitions for color constants.
# define NETTLE 0xAAD4B5
# define WHITE 0xFFFFFF

# define ORANGE '\033[0;33m'
# define GRAY '\033[0;37m'
# define RED '\033[1;31m¬'
# define GREEN '\033[1;32m'

//# include "../lib/libft.h"
# include <unistd.h>
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
#endif
