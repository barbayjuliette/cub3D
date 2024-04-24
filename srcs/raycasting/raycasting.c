/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarbay <jbarbay@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 12:04:44 by jbarbay           #+#    #+#             */
/*   Updated: 2024/04/24 11:05:31 by jbarbay          ###   ########.fr       */
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
	ray_data->position_x = data->player_pos[0] + 0.5;
	ray_data->position_y = data->player_pos[1] - 0.5;
	if (data->player_dir == 'N')
	{
		ray_data->direction_x = 0;
		ray_data->direction_y = -1;
		ray_data->camera_plane_x = -0.66;
		ray_data->camera_plane_y = 0;
	}
	if (data->player_dir == 'S')
	{
		ray_data->direction_x = 0;
		ray_data->direction_y = 1;
		ray_data->camera_plane_x = 0.66;
		ray_data->camera_plane_y = 0;
	}
	if (data->player_dir == 'W')
	{
		ray_data->direction_x = -1;
		ray_data->direction_y = 0;
		ray_data->camera_plane_x = 0;
		ray_data->camera_plane_y = 0.66;
	}
	if (data->player_dir == 'E')
	{
		ray_data->direction_x = 1;
		ray_data->direction_y = 0;
		ray_data->camera_plane_x = 0;
		ray_data->camera_plane_y = -0.66;
	}
	return (ray_data);
}

void	calculate_vars(t_game_data *data, t_raycast *ray_data, int x)
{
	ray_data->camera_x = 2 * x / (double)(WIDTH) - 1; //x-coordinate in camera space
	ray_data->ray_dir_x = ray_data->direction_x + ray_data->camera_plane_x * ray_data->camera_x;
	ray_data->ray_dir_y = ray_data->direction_y + ray_data->camera_plane_y * ray_data->camera_x;

	ray_data->map_x = (int)ray_data->position_x;
	ray_data->map_y = (int)ray_data->position_y;

	if (ray_data->ray_dir_x == 0)
		ray_data->delta_dist_x = 1e30;
	else
		ray_data->delta_dist_x = fabs(1 / ray_data->ray_dir_x);

	if (ray_data->ray_dir_y == 0)
		ray_data->delta_dist_y = 1e30;
	else
		ray_data->delta_dist_y = fabs(1 / ray_data->ray_dir_y);
}

void	calculate_steps(t_game_data *data, t_raycast *ray_data, int x)
{
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
}


void	wall_hit(t_game_data *data, t_raycast *ray_data, int x)
{
	// DDA
	// We hit the shortest one.
	ray_data->hit = 0;
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
}

// Calculate the distance to the wall, using fisheye correction
// Store which side of the wall was hit
// The value wall_X represents the exact value where the wall was hit, not just the integer coordinates of the wall.
// If side == 1, it is a y-coordinate, if side == 0, it is an x-coordinate
// But it is always an x-coordinate for the texture, becasue we do vertical lines
// This is required to know which x-coordinate of the texture we have to use.
// We get 5.34 --> 0.34 to have where on the image. So we know which pixel of the image to render.

void	calculate_ray(t_game_data *data, t_raycast *ray_data)
{

	if (ray_data->side == 0)
	{
		ray_data->perp_wall_dist = ray_data->side_dist_x - ray_data->delta_dist_x;
		ray_data->wall_x = ray_data->position_y + (ray_data->perp_wall_dist * ray_data->ray_dir_y);
	}
	else
	{
		ray_data->perp_wall_dist = ray_data->side_dist_y - ray_data->delta_dist_y;
		ray_data->wall_x = ray_data->position_x + (ray_data->perp_wall_dist * ray_data->ray_dir_x);
	}
	ray_data->wall_x -= floor(ray_data->wall_x);
}

// tex_x refers to the x coordinate on the texture. We are drawing vertical lines, so for now we only need x.
// replace ray_data->text->width with (ray_data->text->line_len / 4) ?

// Now that we know the x-coordinate of the texture, we know that this coordinate will remain the same,
// because we stay in the same vertical stripe of the screen.
// Now we need a loop in the y-direction to give each pixel of the vertical stripe the correct y-coordinate of the texture,
//  called texY.

void	get_pixel_texture(t_game_data *data, t_raycast *ray_data)
{
	ray_data->tex_x = (int)(ray_data->wall_x * (double)(ray_data->text->width));

	if (ray_data->side == 0 && ray_data->ray_dir_x > 0)
		ray_data->tex_x = ray_data->text->width - ray_data->tex_x - 1;
	else if (ray_data->side == 1 && ray_data->ray_dir_y < 0)
		ray_data->tex_x = ray_data->text->width - ray_data->tex_x - 1;
}

int		create_trgb(int t, int r, int g, int b)
{
	return(t << 24 | r << 16 | g << 8 | b);
}

void	draw_line(t_game_data *data, t_raycast *ray_data, int x)
{
	int	y;
	int	step_pixel;
	int	address;
	int	*text;

	text = ray_data->text->addr;
	// How much to increase the texture coordinate per screen pixel
	step_pixel = 1.0 * ray_data->text->height / ray_data->line_height;
	// Coordinate of start texture
	ray_data->text_pos = (ray_data->line_start - HEIGHT / 2 + ray_data->line_height / 2) * ray_data->step_pixel;
	y = ray_data->line_start;
	// Add the right pixel from the texture to the address
	// Address of screen = pixel from texture
	while (y < ray_data->line_end)
	{
		ray_data->tex_y = (int)ray_data->text_pos & (ray_data->text->height - 1);
		ray_data->text_pos += step_pixel;
		data->screen->addr[(y * WIDTH) + x] = text[ray_data->text->height * ray_data->tex_x + ray_data->tex_x];
		y++;
	}
}


void	calculate_line(t_game_data *data, t_raycast *ray_data)
{
	ray_data->line_height = (int)(HEIGHT / ray_data->perp_wall_dist);
	ray_data->line_start = (-ray_data->line_height / 2) + (HEIGHT / 2);
	if (ray_data->line_start < 0)
		ray_data->line_start = 0;
	ray_data->line_end = (ray_data->line_height / 2) + (HEIGHT / 2);
	// ray_data->line_end = ray_data->line_start + ray_data->line_height
	if (ray_data->line_end > HEIGHT)
		ray_data->line_end = HEIGHT - 1;
}

void	raycasting(t_game_data *data)
{
	t_raycast	*ray_data;
	int			x;

	x = 0;
	ray_data = initialize_raycasting_data(data);
	while (x < WIDTH)
	{
		calculate_vars(data, ray_data, x);
		calculate_steps(data, ray_data, x);
		wall_hit(data, ray_data, x);
		calculate_ray(data, ray_data);
		// Find the right texture
		ray_data->text = data->north_text;
		calculate_line(data, ray_data);
		get_pixel_texture(data, ray_data);
		draw_line(data, ray_data, x);
		x++;
	}
}
