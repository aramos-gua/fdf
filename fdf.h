/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramos <alejandro.ramos.gua@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 14:35:35 by aramos            #+#    #+#             */
/*   Updated: 2025/04/28 21:20:50 by aramos           ###   ########.fr       */
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
	int			x;	
	int			y;	
	int			z;	
}	t_vertx;

typedef struct	s_corners
{
	float		x;
	float		y;
}	t_corners;

typedef struct s_mlx_data
{
	//info for MiniLibX
	void		*mlx;//connection pointer
	void		*win;//window pointer
	void		*img;//image pointer(canvas final product)
	char		*addr;//memory that gets changed to build the image
	int			bpp;//bits-per-pixel(usually 32 for RGBA)
	int			line_length;//number of bytes per row
	int			endian;//how color bytes are stored
	//line information
	int			x0;
	int			y0;
	int			x1;
	int			y1;
	//map info
	int			fd;//fd of file
	char		*map_path;//map file
	int			**final_tab;//2D array w/values
	int			map_w;//width/columns
	int			map_h;//height/rows
	int			*row_lengths;//array of row widths
	//position tracking
	int			x;//coordenates
	int			y;//coordenates
	int			i;//var to iterate
	int			col;//current column in 2D
	int			row;//current row in 2D
	//settings for map
	int			scale;//size of squares in grid
	int			translation;//scroll-info
	float		altitude;//change in z
	float		zoom;//zoom value
	float		alpha;//rotation angle
	//3D build-up
	t_vertx		*vertices;//vertices
	t_corners	*corners;//vertices converted to 2D
}	t_data;



//Parse input
void	found_error(char *message);
void	validate_input(t_data *data, char *filename);
int		map_info(t_data *data, char *line);
void	map_parsing(t_data *data);
void	vertices(t_data *data);
void	ver_corn(t_data *data);
void	draw_right(t_data *data);
void	draw_down(t_data *data);
void	ft_draw_line(t_data *data, int color);
