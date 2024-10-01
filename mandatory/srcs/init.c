/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-maaz <ael-maaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 12:33:42 by nhayoun           #+#    #+#             */
/*   Updated: 2024/10/01 18:43:19 by ael-maaz         ###   ########.fr       */
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

void	mock_data(t_data *data)
{
	data->map = malloc(sizeof(char *) * 15);
	data->map[0] = ft_strdup("        111111111111111111111111111");
	data->map[1] = ft_strdup("        1000000000000000000000001");
	data->map[2] = ft_strdup("        101100000111111111100011111");
	data->map[3] = ft_strdup("        1001000000000000000000001");
	data->map[4] = ft_strdup("111111111011000001110000000000001");
	data->map[5] = ft_strdup("100000000011000001110111110111111");
	data->map[6] = ft_strdup("11110111111111011100000010001");
	data->map[7] = ft_strdup("11110111111111011101010010001");
	data->map[8] = ft_strdup("11000000110101011100000010001");
	data->map[9] = ft_strdup("10000000000000001100000010001");
	data->map[10] = ft_strdup("10000000000000001101010010001");
	data->map[11] = ft_strdup("110N000111010101111101111000111");
	data->map[12] = ft_strdup("11110111 1110101 101111010001");
	data->map[13] = ft_strdup("11111111 1111111 111111111111");
	data->map[14] = NULL;
	data->texture1 = mlx_load_png("./textures/texture3.png");
	data->texture2 = mlx_load_png("./textures/ael-maaz.png");
	data->texture3 = mlx_load_png("./textures/wall2.png");
	data->texture4 = mlx_load_png("./textures/wall1.png");
	// data->map = malloc(sizeof(char *) * 15);
	// data->map[0] = ft_strdup("        1111111111111111111111111");
	// data->map[1] = ft_strdup("        1000000000000000000000001");
	// data->map[2] = ft_strdup("        1000000000100000000000001");
	// data->map[3] = ft_strdup("        1000000001010000000000001");
	// data->map[4] = ft_strdup("111111111000000000100000000000001");
	// data->map[5] = ft_strdup("100000000000000000000000000111111");
	// data->map[6] = ft_strdup("10000000000000N0000000010001");
	// data->map[7] = ft_strdup("10000000000000000000000000001");
	// data->map[8] = ft_strdup("11000000000000000000000000001");
	// data->map[9] = ft_strdup("10000000000000000000000000001");
	// data->map[10] = ft_strdup("10000000000000000000000000001");
	// data->map[11] = ft_strdup("11000000000000000000000000001");
	// data->map[12] = ft_strdup("10000001 1000001 100000000001");
	// data->map[13] = ft_strdup("11111111 1111111 111111111111");
	// data->map = malloc(sizeof(char *) * 6);
	// data->map[0] = ft_strdup("1111111");
	// data->map[1] = ft_strdup("1000001");
	// data->map[2] = ft_strdup("100N001");
	// data->map[3] = ft_strdup("1000001");
	// data->map[4] = ft_strdup("1111111");
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
	data->ceiling_color = get_rgba(135, 206, 235, 255);
	data->floor_color = get_rgba(150, 111, 51, 255);
	data->last_x = WIDTH / 2;
	set_direction(data);
}