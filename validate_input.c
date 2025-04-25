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
	int		filen;
	char	*line;

	filen = ft_strlen(filename);
	if (filen < 4 || ft_strncmp(&filename[filen - 4], ".fdf", 4) != 0)
		found_error("Error: Wrong File Format");
	data->fd = open(filename, O_RDONLY);
	if (data->fd < 0)
		found_error("Error: File Error");
	line = get_next_line(data->fd);
	if (!line)
		found_error("Error: Empty or Non-Existent File");
	if (map_info(data, line) < 0)
		found_error("Error: Wrong Map Format");
}

int	map_info(t_data *data, char *line)
{
	data->map_w = word_c(line, ' ');
	while (line)
	{
		if ((int)word_c(line, ' ') != data->map_w)
			return (free(line), -1);
		data->map_h++;
		free(line);
		line = get_next_line(data->fd);
	}
	close(data->fd);
	return (0);
}
