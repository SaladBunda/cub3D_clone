/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-maaz <ael-maaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 12:33:42 by nhayoun           #+#    #+#             */
/*   Updated: 2024/10/04 20:37:07 by ael-maaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	get_height(char **map)
{
	int	i;

	i = 0;
	while (map[i])
		i++;
	return (i * TILE_SIZE);
}

int	get_width(char **map)
{
	int	max;
	int	i;

	i = 0;
	max = 0;
	while (map[i])
	{
		if (ft_strlen(map[i]) > max)
			max = ft_strlen(map[i]);
		i++;
	}
	return ((int)max * TILE_SIZE);
}

void	player_position(t_data *data)
{
	int		i;
	int		j;
	char	**map;

	i = 0;
	map = data->map;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j])
			{
				if (map[i][j] == 'N' || map[i][j] == 'W' || map[i][j] == 'S'
					|| map[i][j] == 'E')
				{
					data->p_x = j * TILE_SIZE;
					data->p_y = i * TILE_SIZE;
					data->p_direction = map[i][j];
				}
			}
			j++;
		}
		i++;
	}
	data->p_x += TILE_SIZE / 2;
	data->p_y += TILE_SIZE / 2;
}

void	mock_data(t_data *data, t_map_data x)
{

	data->textureNO = mlx_load_png(x.no.str);
	data->textureWE = mlx_load_png(x.we.str);
	data->textureSO = mlx_load_png(x.so.str);
	data->textureEA = mlx_load_png(x.ea.str);
	player_position(data);
	if (data->p_direction == 'W')
		data->rot_angle = M_PI;
	if (data->p_direction == 'S')
		data->rot_angle = M_PI / 2 + M_PI;
	if (data->p_direction == 'E')
		data->rot_angle = 0;
	if (data->p_direction == 'N')
		data->rot_angle = M_PI / 2;
	data->h_map = get_height(data->map);
	data->w_map = get_width(data->map);
	// printf("Width: %d Height: %d\n", data->w_map, data->h_map);
	data->p_radius = 60;
	// data->dire = 0;
	data->move_speed = 2;
	data->rot_speed = 4 * (M_PI / 180);
	data->ceiling_color = get_rgba(x.ccolor[0], x.ccolor[1], x.ccolor[2], 255);
	data->floor_color = get_rgba(x.fcolor[0], x.fcolor[1], x.fcolor[2], 255);
	data->last_x = WIDTH / 2;
	set_direction(data);
}