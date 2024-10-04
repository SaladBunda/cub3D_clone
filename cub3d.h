/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-maaz <ael-maaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 12:23:10 by nhayoun           #+#    #+#             */
/*   Updated: 2024/10/04 19:58:47 by ael-maaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include "../MLX42/include/MLX42/MLX42.h"
# include "../libr/libr.h"
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

# define WIDTH 800
# define NOR 800
# define HEIGHT 600
# define TILE_SIZE 10
# define RES 30
# define LINE_HEIGHT 30

# define COLOR_1 get_rgba(255, 0, 255, 255)
# define COLOR_2 get_rgba(0, 0, 0, 255)
# define COLOR_3 get_rgba(139, 0, 0, 255)
# define COLOR_4 get_rgba(112, 128, 144, 255)
# define HOR_COLOR get_rgba(139, 0, 0, 255)
# define VER_COLOR get_rgba(0, 0, 255, 255)
# define FLOOR_COLOR get_rgba(150, 111, 51, 255)
# define SKY_COLOR get_rgba(135, 206, 235, 255)
# define WALL_1 get_rgba(152, 160, 167, 255)
# define WALL_2 get_rgba(140, 141, 141, 255)

# define LEFT 1
# define RIGHT 2
# define DOWN 3
# define UP 4

typedef struct s_util
{
	char *str;
	int count;
} t_util;
typedef struct s_map_data
{
	t_util floor;
	t_util ceiling;
	t_util no;
	t_util so;
	t_util ea;
	t_util we;
	int fcolor[3];
	int ccolor[3];
} t_map_data;

typedef struct s_data
{
	mlx_image_t	*map_img;
	mlx_image_t	*minimap;
	mlx_image_t	*view;
	mlx_texture_t *textureNO;
	mlx_texture_t *textureWE;
	mlx_texture_t *textureSO;
	mlx_texture_t *textureEA;
	mlx_t		*mlx_ptr;
	double		*dist;
	char		**map;
	char		**file;
	double		p_x;
	double		p_y;
	double		p_x1;
	double		p_y1;
	double		first_h_x;
	double		first_h_y;
	double		first_v_x;
	double		first_v_y;
	double		next_h_x;
	double		next_h_y;
	double		next_v_x;
	double		next_v_y;
	double		xa;
	double		ya;
	double		hor_hit_x;
	double		hor_hit_y;
	double		ver_hit_x;
	double		ver_hit_y;
	double		hor_distance;
	double		ver_distance;
	double		p_radius;
	double		rot_angle;
	double		ray_angle;
	int			ray_v_dire;
	int			ray_h_dire;
	double		move_speed;
	double		rot_speed;
	char		p_direction;
	int			v_dire;
	int			h_dire;
	int			w_map;
	int			h_map;
	int			vertical_inter;
	int			ceiling_color;
	int			floor_color;
	double		wall_hit_x;
	double		wall_hit_y;
	double		distance;
	double		last_x;
}				t_data;

typedef struct s_points
{
	double		rad;
	double		p_x1;
	double		p_y1;
	double		dx;
	double		dy;
	double		x_inc;
	double		y_inc;
	double		step;
	int			i;
	double		distance;
}				t_points;

void			render_method(t_data *data);
void			map_render(t_data *data);
void			spawn_player(t_data *data);
double			scaling_value(double ival, double omin, double omax,
					double imax);
int				get_rgba(int r, int g, int b, int a);
// void			draw_line(t_data *data, double distance);
int				in_space(t_data *data);
int				ray_in_corner(t_data *data, double p_x, double p_y);
void			set_direction(t_data *data);
int				point_is_wall(t_data *data, double x, double y);
void			update_dire(t_data *data, double deg);
void			put_background(t_data *data);

void			cast_rays(t_data *data);

// void			draw_vertical_line(t_data *data, int x, int y_start, int y_end);
void draw_vertical_line(t_data *data, int x, int y_start, int y_end, mlx_texture_t *texture);


void			set_intersections(t_data *data, double deg);

double			normalized_angle(double deg);

int				has_wall(t_data *data, double x, double y);

double			pethago_distance(double x2, double x1, double y2, double y1);

void			draw_point(t_data *data, int x, int y, int color);

/* Hooks */
void			keyhooks(mlx_key_data_t keydata, void *param);

void			move_up(mlx_key_data_t keydata, t_data *data);

void			move_up(mlx_key_data_t keydata, t_data *data);
void			move_left(mlx_key_data_t keydata, t_data *data);
void			move_down(mlx_key_data_t keydata, t_data *data);
void			move_right(mlx_key_data_t keydata, t_data *data);

void			mock_data(t_data *data, t_map_data x);

void			mouse_hook(double xdelta, double ydelta, void *param);

char				*ft_strdup_split(const char *s1);

char				*ft_substr_split(char *s, int start, int len);

char				*ft_strjoin_split(char *s1, char *s2);

char				*ft_strchr_split(const char *s, int c);
char	*get_next_line(int fd);
int	ncount(long n);
char	*allocate(int *n, long *i);
void test_function(mlx_t *mlx);
uint32_t get_pixel_color(mlx_texture_t *texture, uint32_t x, uint32_t y);
char	**ft_split(char const *s, char c);
//bunda tests
void test_function(mlx_t *mlx);
uint32_t get_pixel_color(mlx_texture_t *texture, uint32_t x, uint32_t y);
int test_map_validity(char *filename, t_data *data, t_map_data *x);
#endif