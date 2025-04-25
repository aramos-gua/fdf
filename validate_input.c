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
	map_info(data, line);
}

void	map_info(t_data *data, char *line)
{
	char	*c_line;
	int		i;

	i = 0;
	while (line)
	{
		data->map_h++;
		free(line);
		line = get_next_line(data->fd);
	}
	//free(line);
	close(data->fd);
	data->row_lengths = ft_calloc(sizeof(int), data->map_h);
	if (!data->row_lengths)
		found_error("Error: Could Not Allocate for row_lengths");
	data->fd = open(data->map_path, O_RDONLY);
	if (data->fd < 0)
		found_error("Error: Reopen File Error");
	while (i < data->map_h)
	{
		c_line = get_next_line(data->fd);
		if (!c_line)
			found_error("Error: Unexpected EOF");
		data->row_lengths[i] = word_c(c_line, ' ');
		ft_printf("row[%d]: chars: %d %s -> \n", i, data->row_lengths[i], c_line);
		free(c_line);
		i++;
	}
	close(data->fd);
}
