/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transforms.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramos <alejandro.ramos.gua@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 18:09:46 by aramos            #+#    #+#             */
/*   Updated: 2025/04/30 22:20:27 by aramos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	init_bounds(float *min_x, float *max_x, float *min_y, float *max_y)
{
	*min_x = FLT_MAX;
	*max_x = -FLT_MAX;
	*min_y = FLT_MAX;
	*max_y = -FLT_MAX;
}

static void	compute_bounds(t_data *data, float *min_x, float *max_x, float *min_y, float *max_y)
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
		if (i == 0 || iso_x < *min_x)
			*min_x = iso_x;
		if (i == 0 || iso_x > *max_x)
			*max_x = iso_x;
		if (i == 0 || iso_y < *min_y)
			*min_y = iso_y;
		if (i == 0 || iso_y > *max_y)
			*max_y = iso_y;
		i++;
	}
}

static void	calculate_scale_and_offset(t_data *data, float min_x, float max_x, float min_y, float max_y)
{
	float	projected_w;
	float	projected_h;
	float	center_x;
	float	center_y;

	projected_w = max_x - min_x;
	projected_h = max_y - min_y;
	data->scale = fmin(HEIGHT / projected_h, WIDTH / projected_w) * 0.8;
	center_x = (min_x + max_x) / 2.0;
	center_y = (min_y + max_y) / 2.0;
	data->center_x = WIDTH / 2.0 - center_x * data->scale;
	data->center_y = HEIGHT / 2.0 - center_y * data->scale;
//	if (data->center_y > 0)
//		data->center_y = 5;
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
}

void	transforms(t_data *data)
{
	float	min_x;
	float	max_x;
	float	min_y;
	float	max_y;

	if (data->corners)
		free(data->corners);
	data->corners = malloc(data->map_w * data->map_h * sizeof(t_corners));
	if (!data->corners)
		found_error("Error/transforms: Memory allocation failed");
	init_bounds(&min_x, &max_x, &min_y, &max_y);
	compute_bounds(data, &min_x, &max_x, &min_y, &max_y);
	calculate_scale_and_offset(data, min_x, max_x, min_y, max_y);
	apply_transform(data);
}
