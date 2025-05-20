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

#include "../includes_bonus/fdf_bonus.h"

void	reset(t_data *data)
{
	data->scale = 0;
	data->altitude = 0.05;
	data->alpha = M_PI / 6;
	data->translation_y = 0;
	data->translation_x = 0;
	data->rotation_x = 0.0f;
	data->rotation_y = 0.0f;
	data->rotation_z = 0.0f;
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

void	rotate_image(float *x, float *y, float *z, t_data *data)
{
	float	tmp_x;
	float	tmp_y;
	float	tmp_z;

	tmp_y = *y * cos(data->rotation_x) - *z * sin(data->rotation_x);
	tmp_z = *y * sin(data->rotation_x) + *z * cos(data->rotation_x);
	*y = tmp_y;
	*z = tmp_z;
	tmp_x = *x * cos(data->rotation_y) + *z * sin(data->rotation_y);
	tmp_z = -(*x) * sin(data->rotation_y) + *z * cos(data->rotation_y);
	*x = tmp_x;
	*z = tmp_z;
	tmp_x = *x * cos(data->rotation_z) - *y * sin(data->rotation_z);
	tmp_y = *x * sin(data->rotation_z) + *y * cos(data->rotation_z);
	*x = tmp_x;
	*y = tmp_y;
}
