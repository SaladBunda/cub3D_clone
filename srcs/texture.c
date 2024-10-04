/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-maaz <ael-maaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 19:31:29 by ael-maaz          #+#    #+#             */
/*   Updated: 2024/09/15 20:57:09 by ael-maaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

uint32_t get_pixel_color(mlx_texture_t *texture, uint32_t x, uint32_t y)
{
    // Ensure x and y are within bounds
    if (x < 0 || x >= texture->width || y < 0 || y >= texture->height)
        return (0);  // Return 0 for invalid coordinates

    // Calculate the pixel's index in the pixel buffer
    int index = (y * texture->width + x) * 4;

    // Extract RGBA components from the pixel buffer
    uint8_t r = texture->pixels[index + 1]; // Red
    uint8_t g = texture->pixels[index + 2]; // Green
    uint8_t b = texture->pixels[index + 3]; // Blue
    uint8_t a = texture->pixels[index];     // Alpha

    // Combine the color components into a 32-bit color value (0xAARRGGBB)
    uint32_t color = (a << 24) | (r << 16) | (g << 8) | b;

    return color;
}

void test_function(mlx_t *mlx)
{
    mlx_texture_t* texture = mlx_load_png("./textures/wall1.png");
    mlx_image_t* img = mlx_new_image(mlx, texture->width, texture->height);
    printf("%u\n",texture->height);
    uint32_t i = 0;
    uint32_t j = 0;
    while(i < texture->width)
    {
        j = 0;
        while(j < texture->height)
        {
            mlx_put_pixel(img,i,j,get_pixel_color(texture,i,j));
            j++;
        }
        i++;
    }
    // while
    // printf("%u\n",get_pixel_color(texture,0,0));
    // mlx_image_to_window(mlx,img,0,0);
    // mlx_image_to_window(mlx,img,1,1);
    // mlx_image_to_window(mlx,img,2,2);
    // mlx_image_to_window(mlx,img,3,3);
    // mlx_image_to_window(mlx,img,4,4);
    // mlx_image_to_window(mlx,img,5,5);
    // mlx_image_to_window(mlx,img,6,6);
    // mlx_image_to_window(mlx,img,7,7);
    // mlx_image_to_window(mlx,img,8,8);
    // mlx_image_to_window(mlx,img,9,9);
    // mlx_image_to_window(mlx,img,10,10);
    // mlx_image_to_window(mlx,img,11,11);
    // mlx_image_to_window(mlx,img,12,12);
    // mlx_image_to_window(mlx,img,13,13);
    // mlx_image_to_window(mlx,img,14,14);
    // mlx_image_to_window(mlx,img,15,15);
        
    
    (void) img;
    (void) texture;
}
