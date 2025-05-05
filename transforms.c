/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transforms.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramos <alejandro.ramos.gua@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 18:09:46 by aramos            #+#    #+#             */
/*   Updated: 2025/05/05 23:26:22 by aramos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	init_bounds(t_bounds *bounds)
{
	bounds->min_x = FLT_MAX;
	bounds->max_x = -FLT_MAX;
	bounds->min_x = FLT_MAX;
	bounds->max_x = -FLT_MAX;
}

static void	compute_bounds(t_data *data, t_bounds *bounds)
{
	int		i;
	float	x;
	float	y;
	float	z;

	i = 0;
	while (i < data->map_w * data->map_h)
	{
		x = data->vertices[i].x;
		y = data->vertices[i].y;
		z = data->vertices[i].z * data->altitude;
		is_flat(data, x, y, z);
		if (i == 0 || data->iso_x < bounds->min_x)
			bounds->min_x = data->iso_x;
		if (i == 0 || data->iso_x > bounds->max_x)
			bounds->max_x = data->iso_x;
		if (i == 0 || data->iso_y < bounds->min_y)
			bounds->min_y = data->iso_y;
		if (i == 0 || data->iso_y > bounds->max_y)
			bounds->max_y = data->iso_y;
		i++;
	}
}

static void	calculate_scale_and_offset(t_data *data, t_bounds *bounds)
{
	float	proj_w;
	float	proj_h;
	float	center_x;
	float	center_y;

	if (data->scale == 0.0)
	{
		proj_w = bounds->max_x - bounds->min_x;
		proj_h = bounds->max_y - bounds->min_y;
		data->scale_base = fmin(HEIGHT / proj_h, WIDTH / proj_w) * 0.8;
		data->scale = data->scale_base;
	}
	center_x = (bounds->min_x + bounds->max_x) / 2.0;
	center_y = (bounds->min_y + bounds->max_y) / 2.0;
	data->center_x = WIDTH / 2.0 - center_x * data->scale + data->translation_x;
	data->center_y = HEIGHT / 2.0 - center_y * data->scale + data->translation_y;
}

static void	apply_transform(t_data *data)
{
	int		i;
	float	x;
	float	y;
	float	z;

	i = 0;
	while (i < data->map_w * data->map_h)
	{
		x = data->vertices[i].x;
		y = data->vertices[i].y;
		z = data->vertices[i].z * data->altitude;
		is_flat(data, x, y, z);
		data->corners[i].x = data->iso_x * data->scale + data->center_x;
		data->corners[i].y = data->iso_y * data->scale + data->center_y;
		i++;
	}
	i = 0;
}

void	transforms(t_data *data)
{
	t_bounds	bounds;

	if (data->corners)
		free(data->corners);
	data->corners = malloc(data->map_w * data->map_h * sizeof(t_corners));
	if (!data->corners)
		found_error("Error/transforms: Memory allocation failed");
	init_bounds(&bounds);
	compute_bounds(data, &bounds);
	calculate_scale_and_offset(data, &bounds);
	apply_transform(data);
}
