/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grid_maker_helpers.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Alejandro Ramos <alejandro.ramos.gua@gmai  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 18:01:19 by Alejandro Ram     #+#    #+#             */
/*   Updated: 2025/05/19 18:02:29 by Alejandro Ram    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	draw_right(t_data *data)
{
	t_line	line;

	if ((data->i + 1) % data->map_w == 0)
		return ;
	line.a.x = (int)data->corners[data->i].x;
	line.a.y = (int)data->corners[data->i].y;
	line.b.x = (int)data->corners[data->i + 1].x;
	line.b.y = (int)data->corners[data->i + 1].y;
	line.a.color = get_z_color(data->vertices[data->i].z, data);
	line.b.color = get_z_color(data->vertices[data->i + 1].z, data);
	ft_draw_line(data, line);
}

void	draw_down(t_data *data)
{
	t_line	line;

	if ((data->row + 1) >= data->map_h)
		return ;
	line.a.x = (int)data->corners[data->i].x;
	line.a.y = (int)data->corners[data->i].y;
	line.b.x = (int)data->corners[data->i + data->map_w].x;
	line.b.y = (int)data->corners[data->i + data->map_w].y;
	line.a.color = get_z_color(data->vertices[data->i].z, data);
	line.b.color = get_z_color(data->vertices[data->i + data->map_w].z, data);
	ft_draw_line(data, line);
}
