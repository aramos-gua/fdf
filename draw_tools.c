/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramos <alejandro.ramos.gua@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 20:56:54 by aramos            #+#    #+#             */
/*   Updated: 2025/04/28 21:41:02 by aramos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	draw_right(t_data *data)
{
	if ((data->i + 1) >= data->map_w)
		return	;
	ft_printf("draw_right\n");
	data->x0 = (int)data->corners[data->i].x;
	data->y0 = (int)data->corners[data->i].y;
	data->x1 = (int)data->corners[data->i + 1].x;
	data->y1 = (int)data->corners[data->i + 1].y;
	ft_draw_line(data, 0xFFFFFFFF);
}

void	draw_down(t_data *data)
{
	if ((data->row + 1) >= data->map_h)
		return	;
	ft_printf("draw_down\n");
	data->x0 = (int)data->corners[data->i].x;
	data->y0 = (int)data->corners[data->i].y;
	data->x1 = (int)data->corners[data->i + data->map_w].x;
	data->y1 = (int)data->corners[data->i + data->map_w].y;
	ft_draw_line(data, 0xFFFFFFFF);
}

int	ft_loop(t_data *data)
{
	ver_corn(data);
	grid_maker(data);
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	return (0);
}
