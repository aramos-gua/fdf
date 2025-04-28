/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramos <alejandro.ramos.gua@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 11:42:40 by aramos            #+#    #+#             */
/*   Updated: 2025/04/28 21:16:17 by aramos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	handle_input(int keysym, t_data *data)
{
	if (keysym == XK_Escape)
	{
		printf("The %d key was pressed\n\n", keysym);
		mlx_destroy_window(data->mlx, data->win);
		mlx_destroy_display(data->mlx);
		free(data->mlx);
		exit(1);
	}
	printf("The %d key was pressed\n", keysym);
	return (0);
}

void	ft_put_pixel(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bpp / 8));
	*(unsigned int *)dst = color;
}

void ft_draw_line(t_data *data, int color)
{
	int dx = abs(data->x1 - data->x0);
	int dy = -abs(data->y1 - data->y0);
	int sx = (data->x0 < data->x1) ? 1 : -1;
	int sy = (data->y0 < data->y1) ? 1 : -1;
	int err = dx + dy;
	int e2;

	while (1)
	{
		ft_put_pixel(data, data->x0, data->y0, color);
		if (data->x0 == data->x1 && data->y0 == data->y1)
			break;
		e2 = 2 * err;
		if (e2 >= dy)
		{
			err += dy;
			data->x0 += sx;
		}
		if (e2 <= dx)
		{
			err += dx;
			data->y0 += sy;
		}
	}
}

void	grid_maker(t_data *data)
{
	data->row = 1;
	data->i = 0;

	while (data->row < data->map_h)
	{
		data->col = 1;
		while (data->col < data->map_w)
		{
			draw_right(data);//maybe will be able to do int flags here
			draw_down(data);
		}
		if (data->col == data->map_w)
			draw_down(data);
		data->row++;
	}
	data->col = 1;
	if (data->row == data->map_h)
	{
		while (data->col < data->map_w)
			draw_right(data);
	}
	free(data->corners);
}

void	found_error(char *message)
{
	ft_printf("%s\n", message);
	exit (1);
}

void	data_init(t_data *data, char **argv)
{
	data->y = 0;
	data->x = 0;
	data->map_h = 0;
	data->map_w = 0;
	data->scale = 30;
	data->alpha = 7.37;
	data->altitude = 1;
	data->translation = 1;
	data->map_path = argv[1];
}

int	win_init(t_data *data)
{
	data->mlx = mlx_init();
	if (!data->mlx)
		return (free(data->mlx), -1);
	data->win = mlx_new_window(data->mlx, WIDTH, HEIGHT, "Fil de Fer");
	if (!data->win)
		return (-1);
	data->img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	data->addr = mlx_get_data_addr(data->img, &data->bpp,
			&data->line_length, &data->endian);
	ver_corn(data);
	grid_maker(data);
	//mlx_loop_hook(data->mlx, render, data);
	mlx_loop(data->mlx);
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 2)
		found_error("Error: Usage ./fdf map_name.fdf");
	data_init(&data, argv);
	validate_input(&data, data.map_path);
	map_parsing(&data);
	vertices(&data);
	win_init(&data);
	free(data.vertices);
	return (0);
}
	//read_map(argv[1], &data);
	//data.mlx_ptr = mlx_init();
	//if (!data.mlx_ptr)
	//	return (1);
	//data.win_ptr = mlx_new_window(data.mlx_ptr, WIDTH, HEIGHT, "Hello");
	//if (!data.mlx_ptr)
	//{
	//	mlx_destroy_display(data.mlx_ptr);
	//	free(data.mlx_ptr);
	//	return (1);
	//}
	//data.img = mlx_new_image(data.mlx_ptr, WIDTH, HEIGHT);
	//data.addr = mlx_get_data_addr(data.img, 
//&data.bits_per_pixel, &data.line_length, &data.endian);
	//draw_grid(&data, 0xFFFFFFFF);
	//mlx_put_image_to_window(data.mlx_ptr, 
//data.win_ptr, data.img, WIDTH * 0.15, HEIGHT * 0.15);
	//mlx_key_hook(data.win_ptr, handle_input, &data);
	//mlx_loop(data.mlx_ptr);
