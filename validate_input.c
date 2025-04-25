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
	if (!ft_strnstr(data->map_path, ".fdf", filename_len))
		found_error("Error: Wrong File Format");
	data->fd = open(filename, O_RDONLY);
	if (data->fd < 0)
		found_error("Error: File Error");
	line = get_next_line(data->fd);
	if (!line)
		found_error("Error: Empty or Non-Existent File");
	if (map_info(data, line) < 0)
		found_error("Error: Wrong File Content");
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
