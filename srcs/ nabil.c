/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nabil.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-maaz <ael-maaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 14:05:57 by nhayoun           #+#    #+#             */
/*   Updated: 2024/09/22 18:28:39 by ael-maaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	render_wall(t_data *data, int column, double fov)
{
	double	d;
	double	line_height;
	double	wall_height;
	double	projection_plane_distance;

	double y_begin, y_end;
	projection_plane_distance = WIDTH / (2 * tan(fov / 2));
	d = (projection_plane_distance / 2) / tan(fov / 2);
	wall_height = (10 / data->distance) * projection_plane_distance;
	y_begin = (HEIGHT / 2) - (wall_height / 2);
	y_end = (HEIGHT / 2) + (wall_height / 2);
	draw_vertical_line(data, column, (int)y_begin, (int)y_end);
}

void	draw_vertical_line(t_data *data, int x, int y_start, int y_end)
{
	int	y;
    // mlx_image_t* img = mlx_new_image(data->mlx_ptr, texture->width, texture->height);
	// Check if data or data->view is NULL
	if (!data || !data->view)
		return ;
	// Clamp y_start and y_end within valid screen coordinates
	if (y_start < 0)
		y_start = 0;
	if (y_end >= HEIGHT)
		y_end = HEIGHT - 1;
	y = y_start;
	x = WIDTH - x;
	while (y <= y_end)
	{
		if (x < 0 || y < 0 || x >= WIDTH || y >= HEIGHT)
			break ;
		if (!data->vertical_inter)
		{
			mlx_put_pixel(data->view, x, y, WALL_1);
			// mlx_put_pixel(data->view,x,y,get_pixel_color(data->texture1,x,y));
		}
		else
		{
			mlx_put_pixel(data->view, x, y, WALL_2);
			// mlx_put_pixel(data->view,x,y,get_pixel_color(data->texture2,x,y));
		}
		y++;
	}
}

double	cast_ray(t_data *data, double ray_deg)
{
	double	dx;
	double	dy;
	double	step;
	double	p_x;
	double	p_y;
	double	x_inc;
	double	y_inc;
	int		i;

	i = 0;
	p_x = data->p_x;
	p_y = data->p_y;
	dx = data->p_x1 - data->p_x;
	dy = data->p_y1 - data->p_y;
	if (fabs(dx) > fabs(dy))
		step = fabs(dx);
	else
		step = fabs(dy);
	x_inc = dx / step;
	y_inc = dy / step;
	while (i <= step)
	{
		mlx_put_pixel(data->map_img, (int)(round(p_x)), (int)(round(p_y)),get_rgba(255, 0, 0, 255));
		p_x += x_inc;
		p_y += y_inc;
		i++;
	}
	return (0);
}

void	cast_rays(t_data *data)
{
	double angle_increment;
	double distance;
	int column;
	double fov;
	double first_inter_dis;
	double half_fov;
	double angle_offset;

	fov = data->p_radius * (M_PI / 180);
	half_fov = fov / 2;
	angle_offset = fov / (NOR - 1);
	angle_increment = fov / NOR;
	data->ray_angle = data->rot_angle + (fov / 2);
	column = 0;
	while (column < NOR)
	{
		data->ray_angle = normalized_angle(data->rot_angle - half_fov + (column
					* angle_offset));
		update_dire(data, data->ray_angle);
		set_intersections(data, data->ray_angle);
		render_wall(data, column, fov);
		cast_ray(data, data->ray_angle);
		data->ray_angle += angle_increment;
		column++;
	}
}