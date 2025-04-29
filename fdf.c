/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramos <alejandro.ramos.gua@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 11:42:40 by aramos            #+#    #+#             */
/*   Updated: 2025/04/28 22:32:44 by aramos           ###   ########.fr       */
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
	else if (keysym == XK_Down || keysym == XK_Up)
	{
		if (keysym == XK_Down)
			data->scale -= 5;
		else
			data->scale += 5;
		data->img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
		data->addr = mlx_get_data_addr(data->img, &data->bpp, &data->line_length, &data->endian);
		ver_corn(data);
		grid_maker(data);
		mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	}
	printf("The %d key was pressed\n", keysym);
	return (0);
}

void	ft_put_pixel(t_data *data, int x, int y, int color)
{
	char	*dst;

	if ( x < 0 || y < 0 || x >= WIDTH || y >= HEIGHT)
		return ;
	dst = data->addr + (y * data->line_length + x * (data->bpp / 8));
	*(unsigned int *)dst = color;
}

void ft_draw_line(t_data *data, int color)
{
	int x0 = data->x0;
	int y0 = data->y0;
	int x1 = data->x1;
	int y1 = data->y1;

	int dx = abs(x1 - x0);
	int dy = -abs(y1 - y0);
	int sx = (x0 < x1) ? 1 : -1;
	int sy = (y0 < y1) ? 1 : -1;
	int err = dx + dy;
	int e2;

	while (1)
	{
		ft_put_pixel(data, x0, y0, color);
		if (x0 == x1 && y0 == y1)
			break;
		e2 = 2 * err;
		if (e2 >= dy)
		{
			err += dy;
			x0 += sx;
		}
		if (e2 <= dx)
		{
			err += dx;
			y0 += sy;
		}
	}
}
//
//void ft_draw_line(t_data *data, int color)
//{
//	ft_printf("ft_draw_line\n");
//	int dx = abs(data->x1 - data->x0);
//	int dy = -abs(data->y1 - data->y0);
//	int sx = (data->x0 < data->x1) ? 1 : -1;
//	int sy = (data->y0 < data->y1) ? 1 : -1;
//	int err = dx + dy;
//	int e2;
//
//	while (1)
//	{
//		ft_put_pixel(data, data->x0, data->y0, color);
//		if (data->x0 == data->x1 && data->y0 == data->y1)
//			break;
//		e2 = 2 * err;
//		if (e2 >= dy)
//		{
//			err += dy;
//			data->x0 += sx;
//		}
//		if (e2 <= dx)
//		{
//			err += dx;
//			data->y0 += sy;
//		}
//	}
//}

void	grid_maker(t_data *data)
{
	ft_printf("grid_maker\n");
	data->row = 0;
	data->i = 0;

	ft_printf("data->map_h = %d\n data->map_w = %d\n", data->map_h, data->map_w);
	while (data->row < data->map_h)
	{
		data->col = 0;
		while (data->col < data->map_w)
		{
			if (data->col < data->map_w - 1)
				draw_right(data);
			if (data->row < data->map_h - 1)
				draw_down(data);
			ft_printf("data->i = %d\n", data->i);
			data->i++;
			ft_printf("data->col = %d\n", data->col);
			data->col++;
		}
			ft_printf("data->row = %d\n", data->row);
		data->row++;
	}
}

void	found_error(char *message)
{
	ft_printf("%s\n", message);
	exit (1);
}

void	data_init(t_data *data, char **argv)
{
	ft_printf("data_init\n");
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
	ft_printf("win_init\n");
	data->mlx = mlx_init();
	if (!data->mlx)
		return (-1);
	data->win = mlx_new_window(data->mlx, WIDTH, HEIGHT, "Fil de Fer");
	if (!data->win)
		return (-1);
	data->img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	data->addr = mlx_get_data_addr(data->img, &data->bpp,
			&data->line_length, &data->endian);
	ver_corn(data);
	grid_maker(data);
	mlx_loop_hook(data->mlx, ft_loop, data);
	mlx_key_hook(data->win, &handle_input, data);
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
