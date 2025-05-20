/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Alejandro Ramos <alejandro.ramos.gua@gmai  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 08:47:36 by Alejandro Ram     #+#    #+#             */
/*   Updated: 2025/05/02 13:26:11 by Alejandro Ram    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/fdf_bonus.h"

void	compute_z_bounds(t_data *data)
{
	int	i;
	int	z;

	i = 0;
	data->min_z = INT_MAX;
	data->max_z = INT_MIN;
	while (i < (data->map_w * data->map_h))
	{
		z = data->vertices[i].z;
		if (z < data->min_z)
			data->min_z = z;
		if (z > data->max_z)
			data->max_z = z;
		i++;
	}
	compute_vertex_colors(data);
}

void	compute_vertex_colors(t_data *data)
{
	int	i;

	i = 0;
	while (i < (data->map_w * data->map_h))
	{
		data->vertices[i].color = get_z_color(data->vertices[i].z, data);
		i++;
	}
}

int	interpolate_color(int c1, int c2, float t)
{
	int	r;
	int	g;
	int	b;

	r = ((1 - t) * ((c1 >> 16) & 0xFF)) + (t * ((c2 >> 16) & 0xFF));
	g = ((1 - t) * ((c1 >> 8) & 0xFF)) + (t * ((c2 >> 8) & 0xFF));
	b = ((1 - t) * (c1 & 0xFF)) + (t * (c2 & 0xFF));
	return ((r << 16) | (g << 8) | b);
}

int	get_z_color(int z, t_data *data)
{
	float	t;

	if (data->max_z == data->min_z)
		return (0xFFFFFF);
	t = (float)(z - data->min_z) / (data->max_z - data->min_z);
	return (interpolate_color(0xFFFFFFFF, 0xFF2D00, t));
}
