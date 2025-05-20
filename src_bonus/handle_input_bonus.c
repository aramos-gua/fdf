/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_input_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Alejandro Ramos <alejandro.ramos.gua@gmai  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 19:39:02 by Alejandro Ram     #+#    #+#             */
/*   Updated: 2025/05/19 19:47:10 by Alejandro Ram    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/fdf_bonus.h"

static void	handle_zoom(int keysym, t_data *data)
{
	if (keysym == XK_Up && data->scale < 1000)
		data->scale *= M_PI;
	else if (keysym == XK_Down && data->scale > 10)
		data->scale /= M_PI;
}

static void	handle_translation(int keysym, t_data *data)
{
	if (keysym == XK_w)
		data->translation_y -= 10;
	else if (keysym == XK_s)
		data->translation_y += 10;
	else if (keysym == XK_a)
		data->translation_x -= 10;
	else if (keysym == XK_d)
		data->translation_x += 10;
}

static void	handle_rotation(int keysym, t_data *data)
{
	if (keysym == XK_z)
		data->rotation_x += 0.5;
	else if (keysym == XK_x)
		data->rotation_x -= 0.5;
	else if (keysym == XK_c)
		data->rotation_y += 0.5;
	else if (keysym == XK_v)
		data->rotation_y -= 0.5;
}

int	handle_input(int keysym, t_data *data)
{
	if (keysym == XK_Escape)
		handle_exit(data);
	else if (keysym == XK_u)
		data->altitude *= 3;
	else if (keysym == XK_j)
		data->altitude /= 3;
	else if (keysym == XK_r)
		reset(data);
	else if (keysym == XK_p)
		data->is_flat = !data->is_flat;
	else if (keysym == XK_Up || keysym == XK_Down)
		handle_zoom(keysym, data);
	else if (keysym == XK_c || keysym == XK_v)
		handle_rotation(keysym, data);
	else if (keysym == XK_z || keysym == XK_x)
		handle_rotation(keysym, data);
	else
		handle_translation(keysym, data);
	redraw(data);
	return (0);
}
