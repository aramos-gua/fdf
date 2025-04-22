/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramos <alejandro.ramos.gua@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 11:42:40 by aramos            #+#    #+#             */
/*   Updated: 2025/04/13 23:10:40 by aramos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdlib.h>
#include "mlx_linux/mlx.h"
#include "libft/libft.h"
#include <stdio.h>
#include <X11/keysym.h>
#define WIDTH 500
#define HEIGHT 500

typedef struct	s_mlx_data
{
	void	*mlx_ptr;//connection pointer
	void	*win_ptr;//window pointer
	void	*img;//image pointer(canvas final product)
	char	*addr;//memory that gets changed to build the image
	int		bits_per_pixel;//how many bits per pixel for the image(usually 32 for RGBA)
	int		line_length;//number of bytes per row
	int		endian;//how color bytes are stored
	//coordinates
	int	y0;
	int	y1;
	int	x0;
	int	x1;
}	t_data;

int	handle_input(int keysym, t_data *data)
{
	if (keysym == XK_Escape)
	{
		printf("The %d key was pressed\n\n", keysym);
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		mlx_destroy_display(data->mlx_ptr);
		free(data->mlx_ptr);
		exit(1);
	}
	printf("The %d key was pressed\n", keysym);
	return (0);
}

void	ft_put_pixel(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void ft_draw_line(t_data *data, int color)
{
	int	dx;
	int	dy;
	int	y;
	int	i;
	int	p;

	i = 0;
	dx = data->x1 - data->x0;
	dy = data->y1 - data->y0;
	if (dx != 0)
	{
		y = data->y0;
		p = 2 * dy - dx;
		while (i++ <= dx + 1)
		{
			ft_put_pixel(data, data->x0 + i, y, color);
			if (p >= 0)
			{
				y += 1;
				p -= (2 * dx);
			}
			p += (2 * dy);
		}
	}
}

int	main(void)
{
	t_data	data;

	data.mlx_ptr = mlx_init();
	if (!data.mlx_ptr)
		return (1);
	data.win_ptr = mlx_new_window(data.mlx_ptr, WIDTH, HEIGHT, "Hello");
	if (!data.mlx_ptr)
	{
		mlx_destroy_display(data.mlx_ptr);
		free(data.mlx_ptr);
		return (1);
	}
	data.img = mlx_new_image(data.mlx_ptr, WIDTH, HEIGHT);
	data.addr = mlx_get_data_addr(data.img, &data.bits_per_pixel, &data.line_length, &data.endian);
	data.x0 = 50;
	data.x1 = 150;
	data.y0 = 50;
	data.y1 = 150;
	ft_draw_line(&data, 0xFFFFFFFF);
	mlx_put_image_to_window(data.mlx_ptr, data.win_ptr, data.img, 0, 0);
	mlx_key_hook(data.win_ptr, handle_input, &data);
	mlx_loop(data.mlx_ptr);
	return (0);
}
