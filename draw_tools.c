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
	if ((data->i + 1) % data->map_w == 0)
		return	;
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
	data->x0 = (int)data->corners[data->i].x;
	data->y0 = (int)data->corners[data->i].y;
	data->x1 = (int)data->corners[data->i + data->map_w].x;
	data->y1 = (int)data->corners[data->i + data->map_w].y;
	ft_draw_line(data, 0xFFFFFFFF);
}

void	ft_put_pixel(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || y < 0 || x >= WIDTH || y >= HEIGHT)
		return ;
	dst = data->addr + (y * data->line_length + x * (data->bpp / 8));
	*(unsigned int *)dst = color;
}

void	draw_line_init(t_data *data, int *sx, int *sy, int *err)
{
	if (data->x0 < data->x1)
		*sx = 1;
	else
		*sx = -1;
	if (data->y0 < data->y1)
		*sy = 1;
	else
		*sy = -1;
	data->dx = abs(data->x1 - data->x0);
	data->dy = -abs(data->y1 - data->y0);
	*err = data->dx + data->dy;
}

int	ft_loop(t_data *data)
{
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	return (0);
}
