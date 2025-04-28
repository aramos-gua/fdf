/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramos <alejandro.ramos.gua@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 11:42:40 by aramos            #+#    #+#             */
/*   Updated: 2025/04/26 23:07:21 by aramos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	handle_input(int keysym, t_data *data)
{
	if (keysym == XK_Escape)
	{
		printf("The %d key was pressed\n\n", keysym);
		mlx_destroy_window(data->mlx, data->win);
		mlx_destroy_display(data->mlx);
		free(data->mlx);
		exit(1);
	}
	printf("The %d key was pressed\n", keysym);
	return (0);
}
//
//void	ft_put_pixel(t_data *data, int x, int y, int color)
//{
//	char	*dst;
//
//	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
//	*(unsigned int *)dst = color;
//}
//
//void	ft_draw_line(t_data *data, int color)
//{
//	int	dx;
//	int	dy;
//	int	x;
//	int	y;
//	int	i;
//	int	p;
//
//	i = 0;
//	dx = data->x1 - data->x0;
//	dy = data->y1 - data->y0;
//	x = data->x0;
//	y = data->y0;
//	if (abs(dx) > abs(dy))
//	{
//		p = 2 * abs(dy) - abs(dx);
//		while (i <= abs(dx))
//		{
//			ft_put_pixel(data, x, y, color);
//			if (dx > 0)
//				x += 1;
//			else
//				x -= 1;
//			if (p >= 0)
//			{
//				if (dy > 0)
//					y += 1;
//				else
//					y -= 1;
//				p -= 2 * abs(dx);
//			}
//			p += (2 * dy);
//			i++;
//		}
//	}
//	else
//	{
//		if (dy == 0)
//			return ;
//		p = 2 * abs(dx) - abs(dy);
//		while (i <= abs(dy))
//		{
//			ft_put_pixel(data, x, y, color);
//			if (dy > 0)
//				y += 1;
//			else
//				y -= 1;
//			if (p >= 0)
//			{
//				if (dx > 0)
//					x += 1;
//				else
//					x -= 1;
//				p -= 2 * abs(dy);
//			}
//			p += 2 * abs(dx);
//			i++;
//		}
//	}
//}
//
//static int	count_width(char *line)
//{
//	int		i;
//	char	**split;
//	int		count;
//
//	i = 0;
//	count = 0;
//	split = ft_split(line, ' ');
//	while (split[count])
//		count++;
//	while (split[i])
//		free(split[i++]);
//	free(split);
//	return (count);
//}
//
//static void	fill_z_matrix_row(int *row, char *line)
//{
//	char	**split;
//	int		i;
//
//	i = 0;
//	split = ft_split(line, ' ');
//	while (split[i])
//	{
//		row[i] = ft_atoi(split[i]);
//		free(split[i]);
//		i++;
//	}
//	free(split);
//}
//
//void	read_map(char *file, t_data *data)
//{
//	int		i;
//	int		y;
//	int		fd;
//	char	*line;
//
//	y = 0;
//	i = 0;
//	fd = open(file, O_RDONLY);
//	if (fd < 0)
//		exit(EXIT_FAILURE);
//	data->height = 0;
//	while ((line = get_next_line(fd)))
//	{
//		if (data->height == 0)
//			data->width = count_width(line);
//		free(line);
//		data->height++;
//	}
//	close(fd);
//	data->z_matrix = malloc(sizeof(int *) * data->height);
//	if (!data->z_matrix)
//		return ;
//	while (i < data->height)
//		data->z_matrix[i++] = malloc (sizeof(int) * data->width);
//	fd = open(file, O_RDONLY);
//	while ((line = get_next_line(fd)))
//	{
//		fill_z_matrix_row(data->z_matrix[y], line);
//		free(line);
//		y++;
//	}
//	close(fd);
//}
//
//void	draw_grid(t_data *data, int color)
//{
//	int	x;
//	int	y;
//	int	zoom;
//
//	y = 0;
//	zoom = 20;
//	while (y < data->height)
//	{
//		x = 0;
//		while (x < data->width)
//		{
//			if (x < data->width - 1)
//			{
//				data->x0 = x * zoom;
//				data->y0 = y * zoom;
//				data->x1 = (x + 1) * zoom;
//				data->y1 = y * zoom;
//			}
//			ft_draw_line(data, color);
//			if (y < data->height - 1)
//			{
//				data->x0 = x * zoom;
//				data->y0 = y * zoom;
//				data->x1 = x * zoom;
//				data->y1 = (y + 1) * zoom;
//			}
//			ft_draw_line(data, color);
//			x++;
//		}
//		y++;
//	}
//}

void	found_error(char *message)
{
	ft_printf("%s\n", message);
	exit (1);
}

void	data_init(t_data *data, char **argv)
{
	data->y = 0;
	data->x = 0;
	data->map_h = 0;
	data->map_w = 0;
	data->scale = 30;
	data->alpha = 7.37;
	data->altitude = 1;
	data->translation = 1;
	data->map_path = argv[1];
}

int	win_init(t_data *data)
{
	data->mlx = mlx_init();
	if (!data->mlx)
		return (free(data->mlx), -1);
	data->win = mlx_new_window(data->mlx, WIDTH, HEIGHT, "Fil de Fer");
	if (!data->win)
		return (-1);
	data->img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	data->addr = mlx_get_data_addr(data->img, &data->bpp,
			&data->line_length, &data->endian);
	mlx_loop_hook(data->mlx, render, data);
	mlx_loop(data->mlx);
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 2)
		found_error("Error: Usage ./fdf map_name.fdf");
	data_init(&data, argv);
	validate_input(&data, data.map_path);
	map_parsing(&data);
	vertices(&data);
	win_init(&data);
	free(data.vertices);
	free(data.corners);
	return (0);
}
	//read_map(argv[1], &data);
	//data.mlx_ptr = mlx_init();
	//if (!data.mlx_ptr)
	//	return (1);
	//data.win_ptr = mlx_new_window(data.mlx_ptr, WIDTH, HEIGHT, "Hello");
	//if (!data.mlx_ptr)
	//{
	//	mlx_destroy_display(data.mlx_ptr);
	//	free(data.mlx_ptr);
	//	return (1);
	//}
	//data.img = mlx_new_image(data.mlx_ptr, WIDTH, HEIGHT);
	//data.addr = mlx_get_data_addr(data.img, 
//&data.bits_per_pixel, &data.line_length, &data.endian);
	//draw_grid(&data, 0xFFFFFFFF);
	//mlx_put_image_to_window(data.mlx_ptr, 
//data.win_ptr, data.img, WIDTH * 0.15, HEIGHT * 0.15);
	//mlx_key_hook(data.win_ptr, handle_input, &data);
	//mlx_loop(data.mlx_ptr);
