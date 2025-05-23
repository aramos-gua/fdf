/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramos <alejandro.ramos.gua@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 14:35:35 by aramos            #+#    #+#             */
/*   Updated: 2025/05/05 23:26:54 by aramos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_BONUS_H
# define FDF_BONUS_H
# ifndef WEIGHT
#  define HEIGHT 1080
#  ifndef WIDTH
#   define WIDTH 1920
#   ifndef FLT_MAX
#    define FLT_MAX 3.402823466e+38F
#    ifndef FLT_MIN
#     define FLT_MIN 1.175494351e-38F
#    endif
#   endif
#  endif
# endif

# include "../minilibx-linux/mlx.h"
# include "../libft/libft.h"
# include <X11/keysym.h>
# include <stdlib.h>
# include <fcntl.h>
# include <math.h>

typedef struct s_vertx
{
	int			x;	
	int			y;	
	int			z;	
	int			color;
}	t_vertx;

typedef struct s_corners
{
	float		x;
	float		y;
}	t_corners;

typedef struct s_data
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
	int			x0;//start line x-axis
	int			y0;//start line y-axis
	int			x1;//end line x-axis
	int			y1;//end line y-axis
	int			dx;//dif start-end x-axis
	int			dy;//dif start-end y-axis
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
	int			scale_base;//size of squares in grid
	int			scale;//modifiable scale
	int			translation_y;//scroll-info
	int			translation_x;//scroll-info
	float		altitude;//change in z
	float		zoom;//zoom value
	float		alpha;//rotation angle
	//3D build-up
	t_vertx		*vertices;//vertices
	t_corners	*corners;//vertices converted to 2D
	float		iso_x;//x after prokection
	float		iso_y;//y after projection
	//transforms
	float		center_x;
	float		center_y;
	float		scale_fax;
	float		scale_fay;
	int			is_flat;//flag to change projections
	float		rotation_x;
	float		rotation_y;
	float		rotation_z;
	//color gradients
	int			min_z;
	int			max_z;
}	t_data;

typedef struct s_line
{
	t_vertx	a;
	t_vertx	b;
}	t_line;

typedef struct s_line_vars
{
	int		dx;
	int		dy;
	int		err;
	int		e2;
	int		step;
	float	t;
}	t_line_vars;

typedef struct s_bounds
{
	float	min_x;
	float	min_y;
	float	max_x;
	float	max_y;
}	t_bounds;

//Parse input
void	found_error(char *message);
void	validate_input(t_data *data, char *filename);
int		map_info(t_data *data, char *line);
void	map_parsing(t_data *data);
void	vertices(t_data *data);
void	data_init(t_data *data, char **argv);
void	grid_maker(t_data *data);
void	draw_right(t_data *data);
void	ft_put_pixel(t_data *data, int x, int y, int color);
void	draw_down(t_data *data);
void	ft_draw_line(t_data *data, t_line line);
void	draw_line_init(t_line *line, t_line_vars *vars);
int		ft_loop(t_data *data);
int		handle_input(int keysym, t_data *data);
void	transforms(t_data *data);
void	compute_z_bounds(t_data *data);
int		get_z_color(int z, t_data *data);
int		handle_exit(t_data *data);
int		interpolate_color(int color1, int color2, float t);
void	update_coordenates(t_line *line, t_line_vars *vars);
void	compute_vertex_colors(t_data *data);
void	reset(t_data *data);
void	redraw(t_data *data);
void	is_flat(t_data *data, float x, float y, float z);
void	rotate_image(float *x, float *y, float *z, t_data *data);
#endif
