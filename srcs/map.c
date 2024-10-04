/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhayoun <nhayoun@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 15:02:58 by nhayoun           #+#    #+#             */
/*   Updated: 2024/09/15 15:59:08 by nhayoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	has_wall(t_data *data, double x, double y)
{
	char	**map;
	int		i;
	int		j;

	map = data->map;
	if (x < 0 || y < 0)
		return (0);
	i = (int)(x / TILE_SIZE);
	j = (int)(y / TILE_SIZE);
	if (!(j > 0 && j * TILE_SIZE < data->h_map && i > 0
			&& i < (int)ft_strlen(map[j])) || map[j][i] == '1')
		return (1);
	return (0);
}

double	row_len(t_data *data, double x)
{
	char	**map;
	int		i;

	map = data->map;
	if (x < 0)
		return (0);
	i = (int)(x / TILE_SIZE);
	return ((double)ft_strlen(map[i]) * TILE_SIZE);
}

double	scaling_value(double ival, double omin, double omax, double imax)
{
	return ((omax - omin) * (ival - 0) / (imax - 0) + omin);
}

void	draw_grid_lines(mlx_image_t *tile, int pos_x, int pos_y, int color)
{
	int	x;
	int	y;

	x = pos_x;
	y = pos_y;
	while (x < pos_x + TILE_SIZE - 1)
	{
		mlx_put_pixel(tile, x, pos_y, color);
		mlx_put_pixel(tile, x, pos_y + TILE_SIZE - 1, color);
		x++;
	}
	while (y < pos_y + TILE_SIZE - 1)
	{
		mlx_put_pixel(tile, pos_x, y, color);
		mlx_put_pixel(tile, pos_x + TILE_SIZE - 1, y, color);
		y++;
	}
}

void	fill_tile(mlx_image_t *tile, int color, int pos_x, int pos_y)
{
	int	x;
	int	y;

	x = 0;
	while (x < TILE_SIZE)
	{
		y = 0;
		while (y < TILE_SIZE)
		{
			mlx_put_pixel(tile, pos_x + x, pos_y + y, color);
			y++;
		}
		mlx_put_pixel(tile, pos_x + x, pos_y + y, color);
		mlx_put_pixel(tile, pos_x + x, pos_y + y, get_rgba(189, 195, 199, 255));
		x++;
	}
	draw_grid_lines(tile, pos_x, pos_y, get_rgba(189, 195, 199, 255));
}

void	draw_row(char *str, t_data *data, int y_pos)
{
	int	i;
	int	x_pos;

	i = 0;
	x_pos = 0;
	while (str[i])
	{
		if (str[i] == '1')
			fill_tile(data->map_img, get_rgba(0, 0, 0, 255), x_pos, y_pos);
		else if (str[i] == '0')
			fill_tile(data->map_img, get_rgba(255, 255, 255, 255), x_pos,
				y_pos);
		else if (str[i] == 'W' || str[i] == 'N' || str[i] == 'E'
			|| str[i] == 'S')
			fill_tile(data->map_img, get_rgba(255, 255, 255, 255), x_pos,
				y_pos);
		x_pos += TILE_SIZE;
		i++;
	}
}

void	map_render(t_data *data)
{
	int	i;
	int	y_pos;

	i = 0;
	y_pos = 0;
	while (data->map[i])
	{
		draw_row(data->map[i], data, y_pos);
		y_pos += TILE_SIZE;
		i++;
	}
}

int	initial_tile(t_data *data, double p_x1, double p_y1)
{
	int	i;
	int	j;
	int	new_i;
	int	new_j;

	i = data->p_y / TILE_SIZE;
	j = data->p_x / TILE_SIZE;
	new_i = data->p_y / TILE_SIZE;
	new_j = data->p_x / TILE_SIZE;
	if (i == new_i && j == new_j)
		return (1);
	return (0);
}
int	checker(t_data *data, double p_x, double p_y)
{
	char	**map;
	int		i;
	int		j;

	map = data->map;
	j = (int)(p_x / TILE_SIZE);
	i = (int)(p_y / TILE_SIZE);
	if (i < 0 || j < 0 || i * TILE_SIZE >= data->h_map || j
		* TILE_SIZE >= data->w_map || ft_strlen(map[i]) * TILE_SIZE < j
		* TILE_SIZE)
		return (1);
	if (map[i][j] == 'N' || map[i][j] == 'W' || map[i][j] == 'S'
		|| map[i][j] == 'E')
		return (0);
	if (map[i][j] == '1' || map[i][j] != '0')
		return (1);
	return (0);
}

void	end_point(t_data *data, double x, double y)
{
	t_points p;

	p.distance = 10;
	p.i = 0;
	p.rad = data->rot_angle;
	p.dx = p.distance * cos(p.rad);
	p.dy = p.distance * (sin(p.rad) * -1);
	p.p_x1 = 50 + p.dx;
	p.p_y1 = 50 + p.dy;
	if (fabs(p.dx) > fabs(p.dy))
		p.step = fabs(p.dx);
	else
		p.step = fabs(p.dy);
	p.x_inc = p.dx / p.step;
	p.y_inc = p.dy / p.step;
	while (p.i <= p.step)
	{
		mlx_put_pixel(data->minimap, (int)(round(x)), (int)(round(y)),
			get_rgba(189, 195, 199, 255));
		x += p.x_inc;
		y += p.y_inc;
		p.i++;
	}
}

void	minimap_render(t_data *data)
{
	int	end_x;
	int	end_y;
	int	x;
	int	y;

	x = 0;
	end_x = data->p_x + 50;
	end_y = data->p_y + 50;
	while ((data->p_x - 50) + x < end_x)
	{
		y = 0;
		while ((data->p_y - 50) + y < end_y)
		{
			if ((data->p_x - 50) + x < 0 || (data->p_y - 50) + y < 0
				|| checker(data, (data->p_x - 50) + x, (data->p_y - 50) + y))
				mlx_put_pixel(data->minimap, x, y, get_rgba(0, 0, 0, 255));
			else if (!checker(data, (data->p_x - 50) + x, (data->p_y - 50) + y))
				mlx_put_pixel(data->minimap, x, y, get_rgba(255, 255, 255,
						255));
			y++;
		}
		x++;
	}
	draw_point(data, 50, 50, get_rgba(0, 255, 0, 255));
	end_point(data, 50, 50);
}

void	render_method(t_data *data)
{
	if (data->map_img)
		mlx_delete_image(data->mlx_ptr, data->map_img);
	if (data->view)
		mlx_delete_image(data->mlx_ptr, data->view);
	if (data->minimap)
		mlx_delete_image(data->mlx_ptr, data->minimap);
	data->map_img = mlx_new_image(data->mlx_ptr, WIDTH, HEIGHT);
	data->view = mlx_new_image(data->mlx_ptr, WIDTH, HEIGHT);
	data->minimap = mlx_new_image(data->mlx_ptr, 500, 500);
	put_background(data);
	//map_render(data);
	cast_rays(data);
	minimap_render(data);
	mlx_image_to_window(data->mlx_ptr, data->view, 0, 0);
	mlx_image_to_window(data->mlx_ptr, data->minimap, 10, 10);
	// mlx_image_to_window(data->mlx_ptr, data->map_img, 100, 100);
}
