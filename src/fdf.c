/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramos <alejandro.ramos.gua@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 11:42:40 by aramos            #+#    #+#             */
/*   Updated: 2025/05/19 18:29:30 by Alejandro Ram    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	handle_input(int keysym, t_data *data)
{
	if (keysym == XK_Escape)
		handle_exit(data);
	return (0);
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

void	data_init(t_data *data, char **argv)
{
	data->y = 0;
	data->x = 0;
	data->fd = -1;
	data->map_w = 0;
	data->map_h = 0;
	data->is_flat = 0;
	data->corners = NULL;
	data->altitude = 0.27;
	data->vertices = NULL;
	data->alpha = M_PI / 5;
	data->final_tab = NULL;
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
	if (!data->img)
		return (-1);
	data->addr = mlx_get_data_addr(data->img, &data->bpp,
			&data->line_length, &data->endian);
	if (!data->addr)
		return (-1);
	if (data->map_h == 0 || data->map_w == 0)
		found_error("Error: Invalid Map Dimensions");
	data->scale = 0.0;
	transforms(data);
	grid_maker(data);
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	mlx_key_hook(data->win, &handle_input, data);
	mlx_hook(data, 10, 0, handle_exit, data);
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
	compute_z_bounds(&data);
	if (win_init(&data) != 0)
		found_error("Error/MiniLibX: Render Error");
	mlx_loop(data.mlx);
	return (0);
}
