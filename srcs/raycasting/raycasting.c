/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarbay <jbarbay@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 12:04:44 by jbarbay           #+#    #+#             */
/*   Updated: 2024/04/24 17:21:39 by jbarbay          ###   ########.fr       */
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
	ray->position_x = data->player_pos[0] + 0.5;
	ray->position_y = data->player_pos[1] - 0.5;
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

void	calculate_vars(t_game_data *data, t_raycast *ray, int x)
{
	ray->camera_x = 2 * x / (double)(WIDTH) - 1; // x-coordinate in camera space
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

void	calculate_steps(t_raycast *ray)
{
	if (ray->ray_dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (ray->position_x - ray->map_x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - ray->position_x) * ray->delta_dist_x;
	}
	if (ray->ray_dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (ray->position_y - ray->map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - ray->position_y) *ray->delta_dist_y;
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
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		// Check if we hit a wall
		if(data->map[ray->map_y][ray->map_x] == '1')
			ray->hit = 1;
	}
}

// Calculate the distance to the wall, using fisheye correction
// Store which side of the wall was hit
// The value wall_X represents the exact value where the wall was hit, not just the integer coordinates of the wall.
// If side == 1, it is a y-coordinate, if side == 0, it is an x-coordinate
// But it is always an x-coordinate for the texture, becasue we do vertical lines
// This is required to know which x-coordinate of the texture we have to use.
// We get 5.34 --> 0.34 to have where on the image. So we know which pixel of the image to render.

void	calculate_ray(t_raycast *ray)
{

	if (ray->side == 0)
	{
		ray->perp_wall_dist = ray->side_dist_x - ray->delta_dist_x;
		ray->wall_x = ray->position_y + ray->perp_wall_dist * ray->ray_dir_y;
	}
	else
	{
		ray->perp_wall_dist = ray->side_dist_y - ray->delta_dist_y;
		ray->wall_x = ray->position_x + ray->perp_wall_dist * ray->ray_dir_x;
	}
	ray->wall_x -= floor(ray->wall_x);
}

// tex_x refers to the x coordinate on the texture. For one line, tex_x is constant.

// Now that we know the x-coordinate of the texture, we know that this coordinate will remain the same,
// because we stay in the same vertical stripe of the screen.
// Now we need a loop in the y-direction to give each pixel of the vertical stripe the correct y-coordinate of the texture,
//  called texY.

void	get_pixel_texture(t_raycast *ray)
{
	ray->tex_x = (int)(ray->wall_x * (double)(ray->text->width));

	if (ray->side == 0 && ray->ray_dir_x > 0)
		ray->tex_x = ray->text->width - ray->tex_x - 1;
	else if (ray->side == 1 && ray->ray_dir_y < 0)
		ray->tex_x = ray->text->width - ray->tex_x - 1;
}

int		create_trgb(int t, int r, int g, int b)
{
	return(t << 24 | r << 16 | g << 8 | b);
}

// Coordinate of start texture
// How much to increase the texture coordinate per screen pixel
// Add the right pixel from the texture to the address
// Address of screen = pixel from texture

void	draw_line(t_game_data *data, t_raycast *ray, int x)
{
	int		y;
	double	step_pixel;
	double	text_pos;
	int		*text;

	text = ray->text->addr;
	step_pixel = 1.0 * ray->text->height / ray->line_height;
	text_pos = (ray->line_start - HEIGHT / 2 + ray->line_height / 2) * step_pixel;

	y = ray->line_start;
	while (y < ray->line_end)
	{
		ray->tex_y = (int)text_pos % (HEIGHT); // CHANGED
		data->screen->addr[(y * WIDTH) + x] = text[(ray->tex_y * ray->text->width) + ray->tex_x];
		text_pos += step_pixel;
		y++;
	}
}


void	calculate_line(t_game_data *data, t_raycast *ray)
{
	ray->line_height = (int)(HEIGHT / ray->perp_wall_dist);
	ray->line_start = (-ray->line_height / 2) + (HEIGHT / 2);
	if (ray->line_start < 0)
		ray->line_start = 0;
	ray->line_end = (ray->line_height / 2) + (HEIGHT / 2);
	// ray->line_end = ray->line_start + ray->line_height;
	if (ray->line_end > HEIGHT)
		ray->line_end = HEIGHT - 1;
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
		calculate_vars(data, ray, x);
		calculate_steps(ray);
		wall_hit(data, ray);
		calculate_ray(ray);
		choose_texture(data, ray);
		calculate_line(data, ray);
		get_pixel_texture(ray);
		draw_line(data, ray, x);
		x++;
	}
}
