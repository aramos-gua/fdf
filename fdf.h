/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramos <alejandro.ramos.gua@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 14:35:35 by aramos            #+#    #+#             */
/*   Updated: 2025/04/23 14:36:12 by aramos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_linux/mlx.h"
#include "libft/libft.h"
#include <X11/keysym.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <math.h>
#define HEIGHT 500
#define WIDTH 500

typedef struct s_mlx_data
{
	void	*mlx_ptr;//connection pointer
	void	*win_ptr;//window pointer
	void	*img;//image pointer(canvas final product)
	char	*addr;//memory that gets changed to build the image
	int		bits_per_pixel;//how many bits per pixel for the image(usually 32 for RGBA)
	int		line_length;//number of bytes per row
	int		endian;//how color bytes are stored
	//coordinates
	int		y0;
	int		y1;
	int		x0;
	int		x1;
	//map storage
	int		**z_matrix;
	int		width;
	int		height;
	//extra
	int		zoom;
	int		offset_x;
	int		offset_y;
}	t_data;

typedef struct pointer
{
	int	x;	
	int	y;	
	int	z;	
}	t_point;
