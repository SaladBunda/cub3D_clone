/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-maaz <ael-maaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 14:05:57 by nhayoun           #+#    #+#             */
/*   Updated: 2024/10/01 18:44:47 by ael-maaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void render_wall(t_data *data, int column, double fov)
{
    double wall_height;
    double projection_plane_distance;
    double y_begin, y_end;

    // Calculate the distance to the projection plane
    projection_plane_distance = WIDTH / (2 * tan(fov / 2));

    // Calculate wall height based on the unmodified distance (no angle correction)
    wall_height = (TILE_SIZE / data->distance) * projection_plane_distance;

    // Calculate where to begin and end drawing the wall on the screen
    y_begin = (HEIGHT / 2) - (wall_height / 2);
    y_end = (HEIGHT / 2) + (wall_height / 2);

    // Render the wall with the calculated height for both vertical and horizontal intersections
    if (!data->vertical_inter)
    {
        if(data->ray_v_dire == UP)
        {
            draw_vertical_line(data, column, (int)y_begin, (int)y_end, data->texture1);  // Horizontal wall
        }
        else
        {
            draw_vertical_line(data, column, (int)y_begin, (int)y_end, data->texture3);
        }
    }
    else
    {
        if(data->ray_h_dire == LEFT)
        {
            draw_vertical_line(data, column, (int)y_begin, (int)y_end, data->texture2);  // Vertical wall   
        }
        else
            draw_vertical_line(data, column, (int)y_begin, (int)y_end, data->texture4);
    }
}

void draw_vertical_line(t_data *data, int x, int y_start, int y_end, mlx_texture_t *texture)
{
    int y;
    double texture_y;
    double step;
    double texture_pos;
    double texture_x;

    // Safety check to ensure data and texture are not null
    if (!data || !data->view || !texture)
        return;

    // Calculate texture X coordinate based on the intersection point
    // Horizontal walls: use p_x to determine the X position in the texture
    // Vertical walls: use p_y
    if (!data->vertical_inter)
    {
        texture_x = fmod(data->p_x1, TILE_SIZE) / TILE_SIZE * texture->width;
    }
    else
        texture_x = fmod(data->p_y1, TILE_SIZE) / TILE_SIZE * texture->width;

    step = (double)texture->height / (y_end - y_start);  // Height scaling factor

    texture_pos = 0.0;  // Start at the top of the texture
    y = y_start;
    x = WIDTH - x;
    // Draw the vertical line with the texture
    while (y <= y_end)
    {
        // Calculate the Y coordinate in the texture
        texture_y = (int)texture_pos % texture->height;
        if(y>=0 && y<HEIGHT)
        {
            uint32_t color = get_pixel_color(texture, (int)texture_x, (int)texture_y);
            mlx_put_pixel(data->view, x, y, color);
            
        }

        texture_pos += step;
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
		mlx_put_pixel(data->map_img, (int)(round(p_x)), (int)(round(p_y)), get_rgba(255, 0, 0, 255));
		p_x += x_inc;
		p_y += y_inc;
		i++;
	}
	return (0);
}

void	cast_rays(t_data *data)
{
	double angle_increment;
	int column;
	double fov;
	double half_fov;
	double angle_offset;

	fov = data->p_radius * (M_PI / 180);
	half_fov = fov / 2;
	angle_offset = fov / (WIDTH - 1);
	angle_increment = fov / WIDTH;
	data->ray_angle = data->rot_angle + (fov / 2);
	column = 0;
	while (column < WIDTH)
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
