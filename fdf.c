/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramos <alejandro.ramos.gua@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 11:42:40 by aramos            #+#    #+#             */
/*   Updated: 2025/05/02 11:02:18 by Alejandro Ram    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	handle_input(int keysym, t_data *data)
{
	if (keysym == XK_Escape)
	{
		printf("The %d key was pressed\n\n", keysym);
		handle_exit(data);
	}
	else if (keysym == XK_Down || keysym == XK_Up)
	{
		if (keysym == XK_Down)
			data->scale -= 5;
		else
			data->scale += 5;
		mlx_destroy_image(data->mlx, data->img);
		data->img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
		data->addr = mlx_get_data_addr(data->img, &data->bpp,
				&data->line_length, &data->endian);
		transforms(data);
		grid_maker(data);
		mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	}
	return (0);
}

void	ft_draw_line(t_data *data, t_line line)
{
	t_line_vars	vars;

	draw_line_init(&line, &vars);
	while (1)
	{
		if (vars.dx > -vars.dy)
			vars.t = (float)vars.step / (float)vars.dx;
		else
			vars.t = (float)vars.step / (float)(-vars.dy);
		ft_put_pixel(data, line.a.x, line.a.y, interpolate_color(line.a.color, line.b.color, vars.t));
		if (line.a.x == line.b.x && line.a.y == line.b.y)
			break ;
		vars.e2 = 2 * vars.err;
		update_coordenates(&line, &vars);
		vars.step++;
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
	data->fd = -1;
	data->map_w = 0;
	data->map_h = 0;
	data->corners = NULL;
	data->altitude = 1;
	data->vertices = NULL;
	data->translation = 1;
	data->alpha = M_PI / 6;
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
	if (data->map_h == 0 || data->map_w ==0)
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
	for (int i = 0; i < data.map_h; i++)
		free(data.final_tab[i++]);
	free(data.final_tab);
	mlx_loop(data.mlx);
	return (0);
}
