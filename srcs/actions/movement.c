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

t_raycast	*move_forward(t_game_data *data)
{
	t_raycast	*ray;
	int x;
	int y;

	ray = (t_raycast *)malloc(sizeof(t_raycast));
	if (!ray)
		malloc_error(data);
	ray = data->ray;
	//int oldx = ray->position_x;
	//int oldy = ray->position_y;
	x = ray->position_x + ray->direction_x;
	y = ray->position_y + ray->direction_y;
	//printf("current x: %d\n", oldx);
	//printf("current y: %d\n", oldy);
	//printf("new x: %d\n", x);
	//printf("new y: %d\n", y);
	if(data->map[y][x] && data->map[y][x] != '1')
	{
		ray->position_x += ray->direction_x;
		ray->position_y += ray->direction_y;
	}
	else
		printf("You are facing a wall. Try to move/rotate\n");
	return (ray);
}

t_raycast	*move_back(t_game_data *data)
{
	t_raycast	*ray;
	int x;
	int y;

	ray = (t_raycast *)malloc(sizeof(t_raycast));
	if (!ray)
		malloc_error(data);
	ray = data->ray;
	//int oldx = ray->position_x;
	//int oldy = ray->position_y;
	x = ray->position_x - ray->direction_x;
	y = ray->position_y - ray->direction_y;
	//printf("current x: %d\n", oldx);
	//printf("current y: %d\n", oldy);
	//printf("new x: %d\n", x);
	//printf("new y: %d\n", y);
	if(data->map[y][x] && data->map[y][x] != '1')
	{
		ray->position_x -= ray->direction_x;
		ray->position_y -= ray->direction_y;
	}
	else
		printf("You are facing a wall. Try to move/rotate\n");
	return (ray);
}

t_raycast	*move_left(t_game_data *data)
{
	t_raycast	*ray;
	int x;
	int y;

	ray = (t_raycast *)malloc(sizeof(t_raycast));
	if (!ray)
		malloc_error(data);
	ray = data->ray;
	//int oldx = ray->position_x;
	//int oldy = ray->position_y;
	x = ray->position_x + ray->direction_y;
	y = ray->position_y - ray->direction_x;
	//printf("current x: %d\n", oldx);
	//printf("current y: %d\n", oldy);
	//printf("new x: %d\n", x);
	//printf("new y: %d\n", y);
	if(data->map[y][x] && data->map[y][x] != '1')
	{
		ray->position_x += ray->direction_y;
		ray->position_y -= ray->direction_x;
	}
	else
		printf("You are facing a wall. Try to move/rotate\n");
	return (ray);
}

t_raycast	*move_right(t_game_data *data)
{
	t_raycast	*ray;
	int x;
	int y;

	ray = (t_raycast *)malloc(sizeof(t_raycast));
	if (!ray)
		malloc_error(data);
	ray = data->ray;
	//int oldx = ray->position_x;
	//int oldy = ray->position_y;
	x = ray->position_x - ray->direction_y;
	y = ray->position_y + ray->direction_x;
	//printf("current x: %d\n", oldx);
	//printf("current y: %d\n", oldy);
	//printf("new x: %d\n", x);
	//printf("new y: %d\n", y);
	if(data->map[y][x] && data->map[y][x] != '1')
	{
		ray->position_x -= ray->direction_y;
		ray->position_y += ray->direction_x;
	}
	else
		printf("You are facing a wall. Try to move/rotate\n");
	return (ray);
}