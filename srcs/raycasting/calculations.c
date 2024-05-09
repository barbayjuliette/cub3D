/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculations.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarbay <jbarbay@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 17:55:00 by jbarbay           #+#    #+#             */
/*   Updated: 2024/05/09 14:59:16 by jbarbay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void	calculate_steps(t_raycast *ray)
{
	if (ray->ray_dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (ray->position_x - ray->map_x) * ray->d_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - ray->position_x) * ray->d_dist_x;
	}
	if (ray->ray_dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (ray->position_y - ray->map_y) * ray->d_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - ray->position_y) * ray->d_dist_y;
	}
}

// DDA
// We hit the shortest one.
// Side :
// 		1: We hit the y-side
// 		0: We hit the x-side

void	wall_hit(t_game_data *data, t_raycast *ray)
{
	ray->hit = 0;
	while (!ray->hit)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->d_dist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->d_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (data->map[ray->map_y][ray->map_x] == '1')
			ray->hit = 1;
	}
}

// Calculate the distance to the wall, using fisheye correction
// Store which side of the wall was hit
// The value wall_x represents the exact value where the wall was hit,
// not just the integer coordinates of the wall.
// If side == 1, it is a y-coordinate, if side == 0, it is an x-coordinate
// But it is always an x-coordinate for the texture, because vertical lines
// This is required to know which x-coordinate of the texture we have to use.
// We get 5.34 --> 0.34 to have where on the image.
// So we know which pixel of the image to render.

void	calculate_ray(t_raycast *ray)
{
	if (ray->side == 0)
	{
		ray->perp_wall_dist = ray->side_dist_x - ray->d_dist_x;
		ray->wall_x = ray->position_y + ray->perp_wall_dist * ray->ray_dir_y;
	}
	else
	{
		ray->perp_wall_dist = ray->side_dist_y - ray->d_dist_y;
		ray->wall_x = ray->position_x + ray->perp_wall_dist * ray->ray_dir_x;
	}
	ray->wall_x -= floor(ray->wall_x);
}

// tex_x refers to the x coordinate on the texture.
// For one line, tex_x is constant.
// Now we need a loop in the y-direction to give each pixel of
// the vertical stripe the correct y-coordinate of the texture, called tex_y

void	get_pixel_texture(t_raycast *ray)
{
	ray->tex_x = (int)(ray->wall_x * (double)(ray->text->width));
	if (ray->side == 0 && ray->ray_dir_x > 0)
		ray->tex_x = ray->text->width - ray->tex_x - 1;
	else if (ray->side == 1 && ray->ray_dir_y < 0)
		ray->tex_x = ray->text->width - ray->tex_x - 1;
}

void	calculate_line(t_raycast *ray)
{
	ray->line_h = (int)(HEIGHT / ray->perp_wall_dist);
	ray->line_start = (-ray->line_h / 2) + (HEIGHT / 2);
	if (ray->line_start < 0)
		ray->line_start = 0;
	ray->line_end = (ray->line_h / 2) + (HEIGHT / 2);
	if (ray->line_end > HEIGHT)
		ray->line_end = HEIGHT - 1;
}
