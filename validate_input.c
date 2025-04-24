/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramos <alejandro.ramos.gua@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 13:51:56 by aramos            #+#    #+#             */
/*   Updated: 2025/04/24 14:27:13 by aramos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	validate_input(t_data *data, char *filename)
{
	int		filename_len;
	char	*line;

	filename_len = ft_strlen(filename);
	if (!ft_strnstr(filename, ".fdf", filename_len))
		found_error("Error: Wrong File Format");
	data->fd = open(filename, O_RDONLY);
	if (!data->fd)
		found_error("Error: File Error");
	line = get_next_line(data->fd);
	if (!line)
		found_error("Error: Empty or Non-Existent File");
	free(line);
	map_info(data);
}

void	map_info(t_data *data)
{
	char	*line;
	char	**tab;

	line = get_next_line(data->fd);
	tab = ft_split(line, ' ');
	while (tab[data->map_w])
	{
		free(tab[data->map_w]);
		data->map_w++;
	}
	while (line)
	{
		data->map_h++;
		free(line);
		line = get_next_line(data->fd);
	}
	free(line);
	free(tab);
	close(data->fd);
	ft_printf("map width: %dpx\nmap height: %dpx", data->map_w, data->map_h);
}
