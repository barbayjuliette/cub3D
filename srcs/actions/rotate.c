/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rerender.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akolgano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 16:02:49 by akolgano          #+#    #+#             */
/*   Updated: 2024/04/29 16:02:51 by akolgano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/cub3D.h"

t_raycast	*rotate_right(t_game_data *data)
{
	t_raycast	*ray;
	double		rotSpeed;
	double		oldDirX;
	double		oldPlaneX;

	ray = (t_raycast *)malloc(sizeof(t_raycast));
	if (!ray)
		malloc_error(data);
	ray = data->ray;
	rotSpeed = 0.1;
	oldDirX = ray->direction_x;
	ray->direction_x = ray->direction_x * cos(rotSpeed) - ray->direction_y * sin(rotSpeed);
	ray->direction_y = oldDirX * sin(rotSpeed) + ray->direction_y * cos(rotSpeed);
	oldPlaneX = ray->camera_plane_x;
	ray->camera_plane_x = ray->camera_plane_x * cos(rotSpeed) - ray->camera_plane_y * sin(rotSpeed);
	ray->camera_plane_y = oldPlaneX * sin(rotSpeed) + ray->camera_plane_y * cos(rotSpeed);
	return (ray);
}

t_raycast	*rotate_left(t_game_data *data)
{
	t_raycast	*ray;
	double		rotSpeed;
	double		oldDirX;
	double		oldPlaneX;

	ray = (t_raycast *)malloc(sizeof(t_raycast));
	if (!ray)
		malloc_error(data);
	ray = data->ray;
	rotSpeed = 0.1;
	oldDirX = ray->direction_x;
	ray->direction_x = ray->direction_x * cos(-rotSpeed) - ray->direction_y * sin(-rotSpeed);
	ray->direction_y = oldDirX * sin(-rotSpeed) + ray->direction_y * cos(-rotSpeed);
	oldPlaneX = ray->camera_plane_x ;
	ray->camera_plane_x = ray->camera_plane_x * cos(-rotSpeed) - ray->camera_plane_y * sin(-rotSpeed);
	ray->camera_plane_y = oldPlaneX * sin(-rotSpeed) + ray->camera_plane_y * cos(-rotSpeed);
	return (ray);
}