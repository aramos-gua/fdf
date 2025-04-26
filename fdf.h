/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramos <alejandro.ramos.gua@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 14:35:35 by aramos            #+#    #+#             */
/*   Updated: 2025/04/26 21:37:52 by aramos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_linux/mlx.h"
#include "libft/libft.h"
#include <X11/keysym.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <math.h>
#define HEIGHT 600
#define WIDTH 600

typedef struct	s_vertx
{
	int	x;	
	int	y;	
	int	z;	
}	t_vertx;

typedef struct s_mlx_data
{
	//info for MiniLibX
	void	*mlx;//connection pointer
	void	*win;//window pointer
	void	*img;//image pointer(canvas final product)
	char	*addr;//memory that gets changed to build the image
	int		bpp;//bits-per-pixel(usually 32 for RGBA)
	int		line_length;//number of bytes per row
	int		endian;//how color bytes are stored
	//map info
	int		fd;//fd of file
	char	*map_path;//map file
	int		**final_tab;//2D array w/values
	int		map_w;//width/columns
	int		map_h;//height/rows
	int		*row_lengths;//array of row widths
	//position tracking
	int		x;//coordenates
	int		y;//coordenates
	int		i;//coordenates
	int		c_x;//current values
	int		c_y;//current values
	//settings for map
	int		scale;//size of squares in grid
	int		translation;//scroll-info
	float	altitude;//change in z
	float	zoom;//zoom value
	float	alpha;//rotation angle
	//3D vertices
	t_vertx	*s_points;
	//coordinates
	//int		y0;
	//int		y1;
	//int		x0;
	//int		x1;
	//map storage
	//int		**z_matrix;
	//int		width;
	//int		height;
	//extra
	//int		offset_x;
	//int		offset_y;
}	t_data;



//Parse input
void	found_error(char *message);
void	validate_input(t_data *data, char *filename);
int		map_info(t_data *data, char *line);
void	map_parsing(t_data *data);
void	vertices(t_data *data);
