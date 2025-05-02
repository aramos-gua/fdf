/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Alejandro Ramos <alejandro.ramos.gua@gmai  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 08:47:36 by Alejandro Ram     #+#    #+#             */
/*   Updated: 2025/05/02 09:03:42 by Alejandro Ram    ###   ########.fr       */
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
