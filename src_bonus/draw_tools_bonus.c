/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramos <alejandro.ramos.gua@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 20:56:54 by aramos            #+#    #+#             */
/*   Updated: 2025/05/05 23:12:04 by aramos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/fdf_bonus.h"

void	ft_put_pixel(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || y < 0 || x >= WIDTH || y >= HEIGHT)
		return ;
	dst = data->addr + (y * data->line_length + x * (data->bpp / 8));
	*(unsigned int *)dst = color;
}

void	ft_draw_line(t_data *data, t_line line)
{
	t_line_vars	vars;

	draw_line_init(&line, &vars);
	while (1)
	{
		if (vars.dx > -vars.dy)
			vars.t = (float)vars.step / (float)vars.dx;
		else
			vars.t = (float)vars.step / (float)(-vars.dy);
		ft_put_pixel(data, line.a.x, line.a.y,
			interpolate_color(line.a.color, line.b.color, vars.t));
		if (line.a.x == line.b.x && line.a.y == line.b.y)
			break ;
		vars.e2 = 2 * vars.err;
		update_coordenates(&line, &vars);
		vars.step++;
	}
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
