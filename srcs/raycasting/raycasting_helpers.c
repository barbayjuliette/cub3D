/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_helpers.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarbay <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 16:47:40 by jbarbay           #+#    #+#             */
/*   Updated: 2024/05/02 16:47:44 by jbarbay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void	position_north_south(t_raycast *ray, t_game_data *data)
{
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
}

void	position_west_east(t_raycast *ray, t_game_data *data)
{
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
}
