/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transforms.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramos <alejandro.ramos.gua@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 18:09:46 by aramos            #+#    #+#             */
/*   Updated: 2025/04/30 21:39:55 by aramos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	transforms(t_data *data)
{
	int		i;
	float	x;
	float	y;
	float	z;

	i = 0;
	if (data->corners)
		free(data->corners);
	data->corners = malloc(data->map_h * data->map_w * sizeof(t_corners));
	if (!data->corners)
		found_error("Error/vercn: Memory Allocation Failed");
	data->center_x = (data->map_w - 1) / 2.0;
	data->center_y = (data->map_h - 1) / 2.0;
	while (i < (data->map_w * data->map_h))
	{
		x = data->vertices[i].x - data->center_x;
		y = data->vertices[i].y - data->center_y;
		z = -data->vertices[i].z * data->altitude;
		data->corners[i].x = ((x - y) * cos(data->alpha) - z * sin(data->alpha)) *data->scale + WIDTH / 2 + data->translation;
		data->corners[i].y = ((x + y) * sin(data->alpha) + z * cos(data->alpha)) *data->scale + HEIGHT / 2 + data->translation;
		i++;
	}
}
