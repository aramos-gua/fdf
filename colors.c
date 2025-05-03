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

#include "fdf.h"

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
	g = ((1 - t) * ((c1 >> 8) & 0x44)) + (t * ((c2 >> 8) & 0x44));
	b = ((1 - t) * (c1 & 0xDD)) + (t * (c2 & 0xDD));
	return ((r << 16) | (g << 8) | b);
}

int	get_z_color(int z, t_data *data)
{
	float	t;
	int		r;
	int		g;
	int		b;

	t = (float)(z - data->min_z) / (data->max_z - data->min_z);
	if (data->max_z == data->min_z)
		return (0xFFFFFF);
	r = (int)(t * 255);
	g = (int)(128 + t * 127);
	b = (int)((1.0f - t) * 255);
	return ((r << 16) | (g << 8) | b);
}
