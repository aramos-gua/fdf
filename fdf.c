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
		data->addr = mlx_get_data_addr(data->img, &data->bpp,
				&data->line_length, &data->endian);
		if (data->corners)
			free(data->corners);
		ver_corn(data);
		grid_maker(data);
		mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	}
	return (0);
}

void	ft_draw_line(t_data *data, int color)
{
	int	sx;
	int	sy;
	int	err;
	int	e2;

	draw_line_init(data, &sx, &sy, &err);
	while (1)
	{
		ft_put_pixel(data, data->x0, data->y0, color);
		if (data->x0 == data->x1 && data->y0 == data->y1)
			break ;
		e2 = 2 * err;
		if (e2 >= data->dy)
		{
			err += data->dy;
			data->x0 += sx;
		}
		if (e2 <= data->dx)
		{
			err += data->dx;
			data->y0 += sy;
		}
	}
}

void	grid_maker(t_data *data)
{
	data->row = 0;
	data->i = 0;
	while (data->row < data->map_h)
	{
		data->col = 0;
		while (data->col < data->map_w)
		{
			if (data->col < data->map_w - 1)
				draw_right(data);
			if (data->row < data->map_h - 1)
				draw_down(data);
			data->i++;
			data->col++;
		}
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
	data->y = 0;
	data->x = 0;
	data->map_h = 0;
	data->map_w = 0;
	data->scale = 30;
	data->alpha = 0.523599;
	data->altitude = 0.2;
	data->translation = 1;
	data->map_path = argv[1];
}

int	win_init(t_data *data)
{
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
