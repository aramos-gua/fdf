/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transforms.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramos <alejandro.ramos.gua@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 18:09:46 by aramos            #+#    #+#             */
/*   Updated: 2025/05/19 18:30:53 by Alejandro Ram    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	init_bounds(t_bounds *bounds)
{
	bounds->min_x = FLT_MAX;
	bounds->max_x = -FLT_MAX;
	bounds->min_y = FLT_MAX;
	bounds->max_y = -FLT_MAX;
}

static void	compute_bounds(t_data *data, t_bounds *bounds)
{
	int		i;
	float	x;
	float	y;
	float	z;
	float	iso_x;
	float	iso_y;

	i = 0;
	while (i < data->map_w * data->map_h)
	{
		x = data->vertices[i].x;
		y = data->vertices[i].y;
		z = data->vertices[i].z * data->altitude;
		iso_x = (x - y) * cos(data->alpha);
		iso_y = (x + y) * sin(data->alpha) - z;
		if (i == 0 || iso_x < bounds->min_x)
			bounds->min_x = iso_x;
		if (i == 0 || iso_x > bounds->max_x)
			bounds->max_x = iso_x;
		if (i == 0 || iso_y < bounds->min_y)
			bounds->min_y = iso_y;
		if (i == 0 || iso_y > bounds->max_y)
			bounds->max_y = iso_y;
		i++;
	}
}

static void	calculate_scale_and_offset(t_data *data, t_bounds *bounds)
{
	float	projected_w;
	float	projected_h;
	float	center_x;
	float	center_y;
	if (data->scale == 0.0)
	{
		projected_w = bounds->max_x - bounds->min_x;
		projected_h = bounds->max_y - bounds->min_y;
		data->scale = fmin(HEIGHT / projected_h, WIDTH / projected_w) * 0.5;
	}
	center_x = (bounds->min_x + bounds->max_x) / 2.0;
	center_y = (bounds->min_y + bounds->max_y) / 2.0;
	data->center_x = WIDTH / 2.0 - center_x * data->scale;
	data->center_y = HEIGHT / 2.0 - center_y * data->scale;
}

static void	apply_transform(t_data *data)
{
	int		i;
	float	x;
	float	y;
	float	z;
	float	iso_x;
	float	iso_y;

	i = 0;
	while (i < data->map_w * data->map_h)
	{
		x = data->vertices[i].x;
		y = data->vertices[i].y;
		z = data->vertices[i].z * data->altitude;
		iso_x = (x - y) * cos(data->alpha);
		iso_y = (x + y) * sin(data->alpha) - z;
		data->corners[i].x = iso_x * data->scale + data->center_x;
		data->corners[i].y = iso_y * data->scale + data->center_y;
		i++;
	}
	i = 0;
}

void	transforms(t_data *data)
{
	t_bounds bounds;

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
