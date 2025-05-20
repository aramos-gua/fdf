/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freexit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Alejandro Ramos <alejandro.ramos.gua@gmai  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 09:19:40 by Alejandro Ram     #+#    #+#             */
/*   Updated: 2025/05/02 13:36:46 by Alejandro Ram    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/fdf_bonus.h"

void	found_error(char *message)
{
	ft_printf("%s\n", message);
	exit (1);
}

int	handle_exit(t_data *data)
{
	int	i;

	i = 0;
	if (data->final_tab)
	{
		while (i < data->map_h)
			free(data->final_tab[i++]);
		free(data->final_tab);
	}
	if (data->corners)
		free(data->corners);
	if (data->vertices)
		free(data->vertices);
	mlx_destroy_window(data->mlx, data->win);
	mlx_destroy_image(data->mlx, data->img);
	mlx_destroy_display(data->mlx);
	free(data->mlx);
	exit(0);
}
