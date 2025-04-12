/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramos <alejandro.ramos.gua@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 11:42:40 by aramos            #+#    #+#             */
/*   Updated: 2025/04/10 11:45:10 by aramos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdlib.h>
#include "mlx_linux/mlx.h"
#include "libft/libft.h"
#define WINDOW_WIDTH 1920
#define WINDOW_HEIGHT 1080

typedef struct	s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_data;

//void	ft_putpxl(t_data *data, int x, int y, int color)
//{
//	char	*dst;
//
//	if (x >= 0 && x < WINDOW_WIDTH && y >= 0 && y < WINDOW_HEIGHT)
//	{
//		dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
//		*(unsigned int *)dst = color;
//	}
//}

//void	ft_putln(t_data *data, int x1, int y1, int x2, int y2, int color)
//{
//	int	step;
//	int	x;
//	int	y;
//	int	i;
//	int	delta_x;
//	int	delta_y;
//
//	delta_x = x2 - x1;
//	delta_y = y2 - y1;
//	if (abs(delta_x) >= abs(delta_y))
//		step = abs(delta_x);
//	else
//		step = abs(delta_y);
//	delta_x = delta_x / step;
//	delta_y = delta_y / step;
//	x = x1;
//	y = x1;
//	i = 0;
//	while (i < step)
//	{
//		ft_putpxl(data, x, y, color);
//		x += delta_x;
//		y += delta_y;
//		i++;
//	}
//}

int	main(void)
{
	void	*mlx;
	void	*mlx_win;
	//t_data	img;

	mlx = mlx_init();
	if (!mlx)
		return (ft_printf("Error\n"), 1);
	mlx_win = mlx_new_window(mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "Hello World!");
	//img.img = mlx_new_image(mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	//img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	//ft_putpxl(&img, WINDOW_WIDTH/2, WINDOW_HEIGHT/2, 0xFFFFFFFF);
	for (int y = WINDOW_HEIGHT * 0.0;y < WINDOW_HEIGHT * 1.0; ++y)
	{
		for (int x = WINDOW_WIDTH * 0.0 ; x < WINDOW_WIDTH * 1.0; ++x)
		{
			mlx_pixel_put(mlx, mlx_win, x, y, rand() % 0x1000000);
		}
	}
	//mlx_string_put(mlx, mlx_win, WINDOW_WIDTH/2, WINDOW_HEIGHT/2, 0xFFFFFFFF, "Hello, World!");
	//ft_putln(&img, WINDOW_WIDTH/2, WINDOW_HEIGHT/2, (WINDOW_WIDTH/2) + 20, (WINDOW_HEIGHT/2) + 20, 0xFFFFFFFF);
	//mlx_put_image_to_window(mlx, mlx_win, img.img, WINDOW_WIDTH/2, WINDOW_HEIGHT/2);
	mlx_loop(mlx);
	return (0);
}
