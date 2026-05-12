/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maghumya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 00:31:42 by maghumya          #+#    #+#             */
/*   Updated: 2026/02/05 22:35:26 by maghumya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/miniRT.h"

bool	initialize_window(t_mlx *mlx, int width, int height)
{
	mlx->mlx = mlx_init();
	if (!mlx->mlx)
		return (false);
	mlx->win = mlx_new_window(mlx->mlx, width, height, "miniRT");
	if (!mlx->win)
		return (false);
	mlx->img = mlx_new_image(mlx->mlx, width, height);
	if (!mlx->img)
		return (false);
	mlx->addr = mlx_get_data_addr(mlx->img, &mlx->bpp, &mlx->line_len,
			&mlx->endian);
	if (!mlx->addr)
		return (false);
	mlx->width = width;
	mlx->height = height;
	return (true);
}

void	destroy_window(t_mlx *mlx)
{
	if (mlx->img)
		mlx_destroy_image(mlx->mlx, mlx->img);
	if (mlx->win)
		mlx_destroy_window(mlx->mlx, mlx->win);
}

void	mlx_put_pixel(t_mlx *mlx, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= mlx->width || y < 0 || y >= mlx->height)
		return ;
	dst = mlx->addr + (y * mlx->line_len + x * (mlx->bpp / 8));
	*(unsigned int *)dst = color;
}

int	handle_keypress(int keycode, t_data *data)
{
	if (keycode == 65307)
		handle_close(data);
	return (0);
}

int	handle_close(t_data *data)
{
	destroy_window(&data->mlx);
	clean_scene(&data->scene);
	exit(0);
	return (0);
}
