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

void	map_parsing(t_data *data)
{
	char	*line;
	char	**num;

	data->fd = open(data->map_path, O_RDONLY);
	data->final_tab = malloc(data->map_h * sizeof(int *));
	if (!data->final_tab)
		found_error("Error/ftab: Memory Allocation Failed");
	while (data->y < data->map_h)
	{
		data->final_tab[data->y] = malloc(data->map_w * sizeof(int));
		if (!data->final_tab[data->y])
			found_error("Error/ftabs: Memory Allocation Failed");
		line = get_next_line(data->fd);
		num = ft_split(line, ' ');
		free(line);
		data->x = 0;
		while (data->x < data->map_w)
		{
			data->final_tab[data->y][data->x] = ft_atoi(num[data->x]);
			free(num[data->x]);
			(data->x)++;
		}
		data->y++;
		free(num);
	}
}

void	vertices(t_data *data)
{
	int	i;

	i = 0;
	data->s_points = malloc (data->map_w * data->map_h * sizeof(t_vertx));
	if (!data->s_points)
		found_error("Error/vrtc: Memory Allocation Failed");
	data->y = 0;
	while (data->y < data->map_h)
	{
		data->x = 0;
		while (data->x < data->map_w)
		{
			data->s_points[i] = (t_vertx){data->x, data->y,
				data->final_tab[data->y][data->x]};
			i++;
			data->x++;
		}
		data->y++;
	}
	free_3d_table(data);
}
