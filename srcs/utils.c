/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhayoun <nhayoun@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 17:04:17 by nhayoun           #+#    #+#             */
/*   Updated: 2024/09/15 13:32:39 by nhayoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

double	pethago_distance(double x2, double x1, double y2, double y1)
{
	if ((isinf(x1) || isinf(x2) || isinf(y1) || isinf(y2)))
		return (99999999.0);
	return (sqrt(((x2 - x1) * (x2 - x1)) + ((y2 - y1) * (y2 - y1))));
}

void	put_background(t_data *data)
{
	int	x;
	int	y;
	int	first_half;

	x = 0;
	y = 0;
	first_half = HEIGHT / 2;
	while (x < WIDTH)
	{
		y = 0;
		while (y < first_half)
		{
			mlx_put_pixel(data->view, x, y, data->ceiling_color);
			y++;
		}
		while (y < HEIGHT)
		{
			mlx_put_pixel(data->view, x, y, data->floor_color);
			y++;
		}
		x++;
	}
}

void	update_dire(t_data *data, double deg)
{
	deg = normalized_angle(deg);
	if (deg > 0 && deg < M_PI)
		data->ray_v_dire = UP;
	else
		data->ray_v_dire = DOWN;
	if ((deg < 0.5 * M_PI) || (deg > 1.5 * M_PI))
		data->ray_h_dire = RIGHT;
	else
		data->ray_h_dire = LEFT;
}

void	draw_point(t_data *data, int x, int y, int color)
{
	int	i;
	int	j;

	i = -2;
	j = -2;
	while (i < 2)
	{
		j = 0;
		while (j < 2)
		{
			mlx_put_pixel(data->minimap, x + i, y + j, color);
			j++;
		}
		mlx_put_pixel(data->minimap, x + i, y + j, color);
		i++;
	}
}

double	calc_distance(double x1, double y1, double x2, double y2)
{
	return (sqrt(((x2 - x1) * (x2 - x1)) + ((y2 - y1) * (y2 - y1))));
}

int	get_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}