/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramos <alejandro.ramos.gua@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 23:11:39 by aramos            #+#    #+#             */
/*   Updated: 2025/05/05 23:36:13 by aramos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	reset(t_data *data)
{
	data->scale = 0;
	data->altitude = 0.05;
	data->alpha = M_PI / 6;
	data->translation_y = 0;
	data->translation_x = 0;
}

void	redraw(t_data *data)
{
	mlx_destroy_image(data->mlx, data->img);
	data->img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	data->addr = mlx_get_data_addr(data->img, &data->bpp,
			&data->line_length, &data->endian);
	transforms(data);
	grid_maker(data);
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
}

void	is_flat(t_data *data, float x, float y, float z)
{
	if (data->is_flat)
	{
		data->iso_x = x;
		data->iso_y = y;
	}
	else
	{
		data->iso_x = (x - y) * cos(data->alpha);
		data->iso_y = (x + y) * sin(data->alpha) - z;
	}
}
