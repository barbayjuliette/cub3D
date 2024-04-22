/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarbay <jbarbay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 12:04:44 by jbarbay           #+#    #+#             */
/*   Updated: 2024/04/22 15:56:42 by jbarbay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

// Make sure the camera plane is perpendicular to the direction, 
// but you can change the length of it. 
// The ratio between the length of the direction and the camera plane determinates the FOV.
// Here the direction vector is a bit longer than the camera plane, so the FOV will be smaller than 90°

t_raycast	*initialize_raycasting_data(t_game_data *data)
{
	t_raycast	*ray_data;

	ray_data = (t_raycast *)malloc(sizeof(t_raycast));
	ray_data->position_x = data->player_pos[0];
	ray_data->position_y = data->player_pos[1];
	if (data->player_dir == 'N')
	{
		ray_data->direction_x = 0;
		ray_data->direction_y = -1;
	}
	if (data->player_dir == 'S')
	{
		ray_data->direction_x = 0;
		ray_data->direction_y = 1;
	}
	if (data->player_dir == 'W')
	{
		ray_data->direction_x = -1;
		ray_data->direction_y = 0;
	}
	if (data->player_dir == 'E')
	{
		ray_data->direction_x = 1;
		ray_data->direction_y = 0;
	}
	ray_data->camera_plane_x = ray_data->direction_y;
	ray_data->camera_plane_y = 0.66;
	return (ray_data);
}


void	draw_wall(t_raycast *ray_data, t_game_data *data, int x)
{
	// Calculate height of wall to draw on screen
	ray_data->line_height = (int)(HEIGHT / ray_data->perp_wall_dist);

}

void	calculate_rays(t_game_data *data, t_raycast *ray_data)
{
	int			x;

	x = 0;
	ray_data->hit = 0;
	// Calculate rays.
	while (x < WIDTH)
	{
		ray_data->camera_x = 2 * x / (double)(WIDTH) - 1; //x-coordinate in camera space
		ray_data->ray_dir_x = ray_data->direction_x + ray_data->camera_plane_x * ray_data->camera_x;
		ray_data->ray_dir_y = ray_data->direction_y + ray_data->camera_plane_y * ray_data->camera_x;

		ray_data->map_x = (int)ray_data->position_x;
		ray_data->map_y = (int)ray_data->position_y;

		if (ray_data->ray_dir_x == 0)
			ray_data->delta_dist_x = 1e30;
		else
			ray_data->delta_dist_x = fabs(1/ray_data->ray_dir_x);

		if (ray_data->ray_dir_y == 0)
			ray_data->delta_dist_y = 1e30;
		else
			ray_data->delta_dist_y = fabs(1/ray_data->ray_dir_y);

		if (ray_data->ray_dir_x < 0)
		{
			ray_data->step_x = -1;
			ray_data->side_dist_x = (ray_data->position_x - ray_data->map_x) * ray_data->delta_dist_x;
		}
		else
		{
			ray_data->step_x = 1;
			ray_data->side_dist_x = (ray_data->map_x + 1.0 - ray_data->position_x) *ray_data->delta_dist_x;
		}

		if (ray_data->ray_dir_y < 0)
		{
			ray_data->step_y = -1;
			ray_data->side_dist_y = (ray_data->position_y - ray_data->map_y) * ray_data->delta_dist_y;
		}
		else
		{
			ray_data->step_y = 1;
			ray_data->side_dist_y = (ray_data->map_y + 1.0 - ray_data->position_y) *ray_data->delta_dist_y;
		}

		// DDA
		// We hit the shortest one.
		while (!ray_data->hit)
		{
			if (ray_data->side_dist_x < ray_data->side_dist_y)
			{
				ray_data->side_dist_x += ray_data->delta_dist_x;
				ray_data->map_x += ray_data->step_x;
				ray_data->side = 0; // We hit the x-side
			}
			else
			{
				ray_data->side_dist_y += ray_data->delta_dist_y;
				ray_data->map_y += ray_data->step_y;
				ray_data->side = 1; // We hit the y-side
			}
			// Check if we hit a wall
			if(data->map[ray_data->map_y][ray_data->map_x] == '1')
				ray_data->hit = 1;
		}

		// Calculate the distance to the wall, using fisheye correction
		if (ray_data->side == 0)
			ray_data->perp_wall_dist = ray_data->side_dist_x - ray_data->delta_dist_x;
		else
			ray_data->perp_wall_dist = ray_data->side_dist_y - ray_data->delta_dist_y;

		// draw_wall(ray_data, data, x);
		x++;
	}

}

void	raycasting(t_game_data *data)
{
	t_raycast	*ray_data;

	ray_data = initialize_raycasting_data(data);
	calculate_rays(data, ray_data);
}