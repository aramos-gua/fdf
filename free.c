/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramos <alejandro.ramos.gua@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 21:26:05 by aramos            #+#    #+#             */
/*   Updated: 2025/04/26 21:29:44 by aramos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	free_3d_table(t_data *data)
{
	int	y;

	y = 0;
	while (y < data->map_h)
		free(data->final_tab[y++]);
	free(data->final_tab);
}
