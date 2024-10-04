/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-maaz <ael-maaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 17:10:10 by nhayoun           #+#    #+#             */
/*   Updated: 2024/09/22 18:29:11 by ael-maaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

double	first_hor_intersection(t_data *data, double deg)
{
	data->first_h_x = 0;
	data->first_h_y = 0;
	if (data->ray_v_dire == UP)
		data->first_h_y = floor(data->p_y / TILE_SIZE) * TILE_SIZE - 0.01;
	else
		data->first_h_y = floor(data->p_y / TILE_SIZE) * TILE_SIZE + TILE_SIZE;
	data->first_h_x = (data->p_x + (data->first_h_y - data->p_y) / (tan(deg) *
				-1));
	return (0);
}

double	first_ver_intersection(t_data *data, double deg)
{
	if (data->ray_h_dire == RIGHT)
		data->first_v_x = floor(data->p_x / TILE_SIZE) * TILE_SIZE + TILE_SIZE;
	else
		data->first_v_x = floor(data->p_x / TILE_SIZE) * TILE_SIZE - 0.01;
	data->first_v_y = data->p_y + (data->first_v_x - data->p_x) * (tan(deg) *
			-1);
	return (0);
}

double	hor_intersections(t_data *data, double deg, int *hit_wall)
{
	data->next_h_x = data->first_h_x;
	data->next_h_y = data->first_h_y;
	data->xa = 0;
	data->ya = 0;
	if (data->ray_v_dire == UP)
		data->ya = TILE_SIZE * -1;
	else if (data->ray_v_dire == DOWN)
		data->ya = TILE_SIZE;
	data->xa = data->ya / (tan(deg) * -1);
	while (data->next_h_x <= data->w_map && data->next_h_x >= 0
		&& data->next_h_y <= data->h_map && data->next_h_y >= 0)
	{
		if (has_wall(data, data->next_h_x, data->next_h_y) || has_wall(data,
				data->next_h_x + 0.001, data->next_h_y) || has_wall(data,
				data->next_h_x, data->next_h_y + 0.001))
		{
			*hit_wall = 1;
			data->hor_hit_x = data->next_h_x;
			data->hor_hit_y = data->next_h_y;
			break ;
		}
		else
		{
			data->next_h_x += data->xa;
			data->next_h_y += data->ya;
		}
	}
	return (0);
}

double	ver_intersections(t_data *data, double deg, int *hit_wall)
{
	data->next_v_x = data->first_v_x;
	data->next_v_y = data->first_v_y;
	data->xa = 0;
	data->ya = 0;
	if (data->ray_h_dire == RIGHT)
		data->xa = TILE_SIZE;
	else
		data->xa = TILE_SIZE * -1;
	data->ya = data->xa * (tan(deg) * -1);
	while (data->next_v_x <= data->w_map && data->next_v_x >= 0
		&& data->next_v_y <= data->h_map && data->next_v_y >= 0)
	{
		if (has_wall(data, data->next_v_x, data->next_v_y) || has_wall(data,
				data->next_v_x + 0.01, data->next_v_y) || has_wall(data,
				data->next_v_x, data->next_v_y + 0.01))
		{
			*hit_wall = 1;
			data->ver_hit_x = data->next_v_x;
			data->ver_hit_y = data->next_v_y;
			break ;
		}
		else
		{
			data->next_v_x += data->xa;
			data->next_v_y += data->ya;
		}
	}
}

// void	set_intersections(t_data *data, double deg)
// {
// 	int found_hor_wall;
// 	int found_ver_wall;
// 	double hor_dist;
// 	double ver_dist;

// 	hor_dist = 0;
// 	ver_dist = 0;
// 	found_hor_wall = 0;
// 	found_ver_wall = 0;

// 	// Step 1: Find initial horizontal and vertical intersections
// 	first_hor_intersection(data, deg);
// 	first_ver_intersection(data, deg);

// 	// Step 2: Trace along horizontal and vertical lines to find walls
// 	hor_intersections(data, deg, &found_hor_wall);
// 	ver_intersections(data, deg, &found_ver_wall);

// 	// Step 3: Calculate distances to the horizontal and vertical hits
// 	if (found_hor_wall)
// 	{
// 		hor_dist = pethago_distance(data->hor_hit_x, data->p_x, data->hor_hit_y, data->p_y);
// 		data->wall_hit_x = data->hor_hit_x;  // Store wall hit position for texture mapping
// 		data->wall_hit_y = data->hor_hit_y;
// 	}
// 	else
// 		hor_dist = 9999999.00;

// 	if (found_ver_wall)
// 	{
// 		ver_dist = pethago_distance(data->ver_hit_x, data->p_x, data->ver_hit_y, data->p_y);
// 		data->wall_hit_x = data->ver_hit_x;  // Store wall hit position for texture mapping
// 		data->wall_hit_y = data->ver_hit_y;
// 	}
// 	else
// 		ver_dist = 99999999.00;

// 	// Step 4: Choose the shorter distance (closer wall)
// 	if (hor_dist < ver_dist)
// 	{
// 		data->vertical_inter = 0;  // Horizontal wall
// 		data->p_x1 = data->hor_hit_x;
// 		data->p_y1 = data->hor_hit_y;
// 		data->distance = hor_dist;
// 	}
// 	else
// 	{
// 		data->vertical_inter = 1;  // Vertical wall
// 		data->p_x1 = data->ver_hit_x;
// 		data->p_y1 = data->ver_hit_y;
// 		data->distance = ver_dist;
// 	}

// 	// Step 5: Correct the distance using the cosine of the angle
// 	data->distance *= cos(data->rot_angle - data->ray_angle);
// }


void	set_intersections(t_data *data, double deg)
{
	int found_hor_wall;
	int found_ver_wall;
	double hor_dist;
	double ver_dist;

	hor_dist = 0;
	ver_dist = 0;
	found_hor_wall = 0;
	found_ver_wall = 0;
	first_hor_intersection(data, deg);
	first_ver_intersection(data, deg);
	hor_intersections(data, deg, &found_hor_wall);
	ver_intersections(data, deg, &found_ver_wall);
	if (found_hor_wall)
	{
		hor_dist = pethago_distance(data->hor_hit_x, data->p_x, data->hor_hit_y,
				data->p_y);
	}
	else
		hor_dist = 9999999.00;
	if (found_ver_wall)
	{
		ver_dist = pethago_distance(data->ver_hit_x, data->p_x, data->ver_hit_y,
				data->p_y);
	}
	else
		ver_dist = 99999999.00;
	if (hor_dist < ver_dist)
	{
		data->vertical_inter = 0;
		data->p_x1 = data->hor_hit_x;
		data->p_y1 = data->hor_hit_y;
		data->distance = hor_dist;
	}
	else
	{
		data->vertical_inter = 1;
		data->p_x1 = data->ver_hit_x;
		data->p_y1 = data->ver_hit_y;
		data->distance = ver_dist;
	}
	data->distance *= cos(data->rot_angle - data->ray_angle);
}
