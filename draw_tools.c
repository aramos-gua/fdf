/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramos <alejandro.ramos.gua@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 20:56:54 by aramos            #+#    #+#             */
/*   Updated: 2025/04/28 21:23:08 by aramos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	draw_right(t_data *data)
{
	float	x0;
	float	y0;
	float	x1;
	float	y1;

	x0 = data->corners[data->i].x;
	y0 = data->corners[data->i].y;
	x1 = data->corners[data->i + 1].x;
	y1 = data->corners[data->i + 1].y;
	data->col++;
	ft_draw_line(data, 0xFFFFFFFF;
}

void	draw_down(t_data *data)
{
	float	x0;
	float	y0;
	float	x1;
	float	y1;

	x0 = data->corners[data->i].x;
	y0 = data->corners[data->i].y;
	x1 = data->corners[data->i + data->map_w].x;
	y1 = data->corners[data->i + data->map_w].y;
	ft_draw_line(data, 0xFFFFFFFF;
}
