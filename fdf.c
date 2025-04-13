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

#include <math.h>
#include <stdlib.h>
#include "mlx_linux/mlx.h"
#include "libft/libft.h"
#define WIDTH 500
#define HEIGHT 500

int	main(void)
{
	void	*mlx_connection;
	void	*mlx_window;
	void	*mlx_window2;

	mlx_connection = mlx_init();
	if (!mlx_connection)
		return (ft_printf("Error\n"), 1);
	mlx_window = mlx_new_window(mlx_connection, HEIGHT, WIDTH, ":O");
	if (!mlx_window)
	{
		mlx_destroy_display(mlx_connection);
		free(mlx_connection);
		return (ft_printf("Error\n"), 1);
	}
	mlx_window2 = mlx_new_window(mlx_connection, HEIGHT, WIDTH, "2nd Window");
	if (!mlx_window2)
	{
		mlx_destroy_display(mlx_connection);
		free(mlx_connection);
		return (ft_printf("Error\n"), 1);
	}
	mlx_loop(mlx_connection);
	mlx_destroy_window(mlx_connection, mlx_window);
	mlx_destroy_display(mlx_connection);
	free(mlx_connection);
	return (0);
}
