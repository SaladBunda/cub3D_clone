/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-maaz <ael-maaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 12:22:46 by nhayoun           #+#    #+#             */
/*   Updated: 2024/10/01 19:27:11 by ael-maaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int ac, char **av)
{
	t_data data;

	if(ac == 2)
	{
		if(test_map_validity(av[1], &data) == 1)
		{
			// printf("failed\n");
			return 1;
		}
		mock_data(&data);
		data.mlx_ptr = mlx_init(WIDTH, HEIGHT, "cub3d", 1);
		mlx_key_hook(data.mlx_ptr, keyhooks, (void *)&data);
		mlx_cursor_hook(data.mlx_ptr, mouse_hook, (void *)&data);
		render_method(&data);
		mlx_loop(data.mlx_ptr);
		mlx_terminate(data.mlx_ptr);
	}
	else
		printf("usage: ./cub3D (map path)\n");

}