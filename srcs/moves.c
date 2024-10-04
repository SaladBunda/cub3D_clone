/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhayoun <nhayoun@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 17:52:46 by nhayoun           #+#    #+#             */
/*   Updated: 2024/09/14 17:59:02 by nhayoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	move_up(mlx_key_data_t keydata, t_data *data)
{
	data->p_y -= sin(data->rot_angle) * data->move_speed;
	data->p_x += cos(data->rot_angle) * data->move_speed;
	if (!in_space(data))
	{
		data->p_y += sin(data->rot_angle) * data->move_speed;
		data->p_x -= cos(data->rot_angle) * data->move_speed;
	}
}

void	move_left(mlx_key_data_t keydata, t_data *data)
{
	data->p_y -= cos(data->rot_angle) * data->move_speed;
	data->p_x -= sin(data->rot_angle) * data->move_speed;
	if (!in_space(data))
	{
		data->p_y += cos(data->rot_angle) * data->move_speed;
		data->p_x += sin(data->rot_angle) * data->move_speed;
	}
}

void	move_down(mlx_key_data_t keydata, t_data *data)
{
	data->p_y += sin(data->rot_angle) * data->move_speed;
	data->p_x -= cos(data->rot_angle) * data->move_speed;
	if (!in_space(data))
	{
		data->p_y -= sin(data->rot_angle) * data->move_speed;
		data->p_x += cos(data->rot_angle) * data->move_speed;
	}
}

void	move_right(mlx_key_data_t keydata, t_data *data)
{
	data->p_y += cos(data->rot_angle) * data->move_speed;
	data->p_x += sin(data->rot_angle) * data->move_speed;
	if (!in_space(data))
	{
		data->p_y -= cos(data->rot_angle) * data->move_speed;
		data->p_x -= sin(data->rot_angle) * data->move_speed;
	}
}
