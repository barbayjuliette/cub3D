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
	double		v;
	double		old_dirx;
	double		old_planex;

	ray = (t_raycast *)malloc(sizeof(t_raycast));
	if (!ray)
		malloc_error(data);
	ray = data->ray;
	v = 0.1;
	old_dirx = ray->direction_x;
	ray->direction_x = ray->direction_x * cos(v) - ray->direction_y * sin(v);
	ray->direction_y = old_dirx * sin(v) + ray->direction_y * cos(v);
	old_planex = ray->camera_plane_x;
	ray->camera_plane_x = ray->camera_plane_x * cos(v) - \
		ray->camera_plane_y * sin(v);
	ray->camera_plane_y = old_planex * sin(v) + ray->camera_plane_y * cos(v);
	return (ray);
}

t_raycast	*rotate_left(t_game_data *data)
{
	t_raycast	*ray;
	double		v;
	double		old_dirx;
	double		old_planex;

	ray = (t_raycast *)malloc(sizeof(t_raycast));
	if (!ray)
		malloc_error(data);
	ray = data->ray;
	v = 0.1;
	old_dirx = ray->direction_x;
	ray->direction_x = ray->direction_x * cos(-v) - ray->direction_y * sin(-v);
	ray->direction_y = old_dirx * sin(-v) + ray->direction_y * cos(-v);
	old_planex = ray->camera_plane_x ;
	ray->camera_plane_x = ray->camera_plane_x * cos(-v) - \
		ray->camera_plane_y * sin(-v);
	ray->camera_plane_y = old_planex * sin(-v) + ray->camera_plane_y * cos(-v);
	return (ray);
}
