/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramos <alejandro.ramos.gua@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 11:42:40 by aramos            #+#    #+#             */
/*   Updated: 2025/04/13 23:10:40 by aramos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_linux/mlx.h"
#include "libft/libft.h"
#include <X11/keysym.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <math.h>
#define HEIGHT 500
#define WIDTH 500

typedef struct s_mlx_data
{
	void	*mlx_ptr;//connection pointer
	void	*win_ptr;//window pointer
	void	*img;//image pointer(canvas final product)
	char	*addr;//memory that gets changed to build the image
	int		bits_per_pixel;//how many bits per pixel for the image(usually 32 for RGBA)
	int		line_length;//number of bytes per row
	int		endian;//how color bytes are stored
	//coordinates
	int		y0;
	int		y1;
	int		x0;
	int		x1;
	//map storage
	int		**z_matrix;
	int		width;
	int		height;
	//extra
	int		zoom;
	int		offset_x;
	int		offset_y;
}	t_data;

typedef struct pointer
{
	int	x;	
	int	y;	
	int	z;	
}	t_point;

int	handle_input(int keysym, t_data *data)
{
	if (keysym == XK_Escape)
	{
		printf("The %d key was pressed\n\n", keysym);
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		mlx_destroy_display(data->mlx_ptr);
		free(data->mlx_ptr);
		exit(1);
	}
	printf("The %d key was pressed\n", keysym);
	return (0);
}

void	ft_put_pixel(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	ft_draw_line(t_data *data, int color)
{
	int	dx;
	int	dy;
	int	y;
	int	i;
	int	p;

	i = 0;
	dx = data->x1 - data->x0;
	dy = data->y1 - data->y0;
	if (dx != 0)
	{
		y = data->y0;
		p = 2 * dy - dx;
		while (i++ <= dx + 1)
		{
			ft_put_pixel(data, data->x0 + i, y, color);
			if (p >= 0)
			{
				y += 1;
				p -= (2 * dx);
			}
			p += (2 * dy);
		}
	}
}

static int	count_width(char *line)
{
	int		i;
	char	**split;
	int		count;

	i = 0;
	count = 0;
	split = ft_split(line, ' ');
	while(split[count])
		count++;
	while (split[i])
		free(split[i++]);
	free(split);
	return (count);
}

static void	fill_z_matrix_row(int *row, char *line)
{
	char	**split;
	int		i;

	i = 0;
	split =ft_split(line, ' ');
	while (split[i])
	{
		row[i] = ft_atoi(split[i]);
		free(split[i]);
		i++;
	}
	free(split);
}

void	read_map(char *file, t_data *data)
{
	int		i;
	int		y;
	int		fd;
	char	*line;

	y = 0;
	i = 0;
	fd = open(file, O_RDONLY);
	if (fd < 0)
		exit(EXIT_FAILURE);
	data->height = 0;
	while ((line = get_next_line(fd)))
	{
		if (data->height == 0)
			data->width = count_width(line);
		free(line);
		data->height++;
	}
	close(fd);
	data->z_matrix = malloc(sizeof(int *) * data->height);
	if (!data->z_matrix)
		return ;
	while (i < data->height)
		data->z_matrix[i++] = malloc (sizeof(int) * data->width);
	fd = open(file, O_RDONLY);
	while ((line = get_next_line(fd)))
	{
		fill_z_matrix_row(data->z_matrix[y], line);
		free(line);
		y++;
	}
	close(fd);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 2)
		return (ft_printf("Usage ./fdf map_name.fdf\n"), 1);
	read_map(argv[1], &data);
	data.mlx_ptr = mlx_init();
	if (!data.mlx_ptr)
		return (1);
	data.win_ptr = mlx_new_window(data.mlx_ptr, WIDTH, HEIGHT, "Hello");
	if (!data.mlx_ptr)
	{
		mlx_destroy_display(data.mlx_ptr);
		free(data.mlx_ptr);
		return (1);
	}
	data.img = mlx_new_image(data.mlx_ptr, WIDTH, HEIGHT);
	data.addr = mlx_get_data_addr(data.img, &data.bits_per_pixel, &data.line_length, &data.endian);
	data.x0 = 50;
	data.x1 = 150;
	data.y0 = 50;
	data.y1 = 150;
	ft_draw_line(&data, 0xFFFFFFFF);
	mlx_put_image_to_window(data.mlx_ptr, data.win_ptr, data.img, 0, 0);
	mlx_key_hook(data.win_ptr, handle_input, &data);
	mlx_loop(data.mlx_ptr);
	return (0);
}
