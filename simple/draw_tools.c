/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramos <alejandro.ramos.gua@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 20:56:54 by aramos            #+#    #+#             */
/*   Updated: 2025/05/02 10:56:34 by Alejandro Ram    ###   ########.fr       */
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

void	ft_put_pixel(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || y < 0 || x >= WIDTH || y >= HEIGHT)
		return ;
	dst = data->addr + (y * data->line_length + x * (data->bpp / 8));
	*(unsigned int *)dst = color;
}

void	update_coordenates(t_line *line, t_line_vars *vars)
{
	if (vars->e2 >= vars->dy)
	{
		vars->err += vars->dy;
		if (line->a.x < line->b.x)
			line->a.x += 1;
		else
			line->a.x += -1;
	}
	if (vars->e2 <= vars->dx)
	{
		vars->err += vars->dx;
		if (line->a.y < line->b.y)
			line->a.y += 1;
		else
			line->a.y += -1;
	}
}

void	draw_line_init(t_line *line, t_line_vars *vars)
{
	vars->dx = abs(line->b.x - line->a.x);
	vars->dy = -abs(line->b.y - line->a.y);
	vars->err = vars->dx + vars->dy;
	vars->step = 0;
}
