/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramos <alejandro.ramos.gua@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 13:51:56 by aramos            #+#    #+#             */
/*   Updated: 2025/04/24 16:13:32 by aramos           ###   ########.fr       */
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
	map_info(data, line);
}

void	map_info(t_data *data, char *line)
{
	data->map_w = word_c(line, ' ');
	while (line)
	{
		data->map_h++;
		free(line);
		line = get_next_line(data->fd);
	}
	free(line);
	close(data->fd);
}


