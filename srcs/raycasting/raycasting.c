/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarbay <jbarbay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 12:04:44 by jbarbay           #+#    #+#             */
/*   Updated: 2024/04/25 12:22:02 by jbarbay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

// Make sure the camera plane is perpendicular to the direction,
// but you can change the length of it.
// The ratio between the length of the direction and the camera plane determinates the FOV.
// Here the direction vector is a bit longer than the camera plane, so the FOV will be smaller than 90°

t_raycast	*initialize_raycasting_data(t_game_data *data)
{
	t_raycast	*ray;

	ray = (t_raycast *)malloc(sizeof(t_raycast));
	data->ray = ray;
	ray->position_x = data->player_pos[0] + 0.5;
	ray->position_y = data->player_pos[1] + 0.5;
	if (data->player_dir == 'N')
	{
		ray->direction_x = 0;
		ray->direction_y = -1;
		ray->camera_plane_x = 0.66;
		ray->camera_plane_y = 0;
	}
	if (data->player_dir == 'S')
	{
		ray->direction_x = 0;
		ray->direction_y = 1;
		ray->camera_plane_x = -0.66;
		ray->camera_plane_y = 0;
	}
	if (data->player_dir == 'W')
	{
		ray->direction_x = -1;
		ray->direction_y = 0;
		ray->camera_plane_x = 0;
		ray->camera_plane_y = -0.66;
	}
	if (data->player_dir == 'E')
	{
		ray->direction_x = 1;
		ray->direction_y = 0;
		ray->camera_plane_x = 0;
		ray->camera_plane_y = 0.66;
	}
	return (ray);
}

void	calculate_vars(t_raycast *ray, int x)
{
	ray->camera_x = 2 * x / (double)(WIDTH) - 1;
	ray->ray_dir_x = ray->direction_x + ray->camera_plane_x * ray->camera_x;
	ray->ray_dir_y = ray->direction_y + ray->camera_plane_y * ray->camera_x;

	ray->map_x = (int)ray->position_x;
	ray->map_y = (int)ray->position_y;

	if (ray->ray_dir_x == 0)
		ray->delta_dist_x = 1e30;
	else
		ray->delta_dist_x = fabs(1 / ray->ray_dir_x);

	if (ray->ray_dir_y == 0)
		ray->delta_dist_y = 1e30;
	else
		ray->delta_dist_y = fabs(1 / ray->ray_dir_y);
}

// We check the coordinate of the player against the coordinate where the wall was hit.

void	choose_texture(t_game_data *data, t_raycast *ray)
{
	if (ray->side == 1)
	{
		if (ray->position_y < ray->map_y)
			ray->text = data->south_text;
		else
			ray->text = data->north_text;
	}
	else
	{
		if (ray->position_x < ray->map_x)
			ray->text = data->east_text;
		else
			ray->text = data->west_text;
	}
}

void	raycasting(t_game_data *data)
{
	t_raycast	*ray;
	int			x;

	x = 0;
	ray = initialize_raycasting_data(data);
	while (x < WIDTH)
	{
		calculate_vars(ray, x);
		calculate_steps(ray);
		wall_hit(data, ray);
		calculate_ray(ray);
		choose_texture(data, ray);
		calculate_line(ray);
		get_pixel_texture(ray);
		draw_line(data, ray, x);
		draw_floor(data, ray, x);
		draw_ceiling(data, ray, x);
		x++;
	}
}
