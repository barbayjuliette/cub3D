/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarbay <jbarbay@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 17:50:28 by jbarbay           #+#    #+#             */
/*   Updated: 2024/05/09 15:21:17 by jbarbay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

// Coordinate of start texture
// How much to increase the texture coordinate per screen pixel
// Add the right pixel from the texture to the address
// Address of screen = pixel from texture

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

void	draw_line(t_game_data *data, t_raycast *ray, int x)
{
	int		y;
	double	step_pixel;
	double	text_pos;
	int		*text;

	text = ray->text->addr;
	step_pixel = 1.0 * ray->text->height / ray->line_h;
	text_pos = (ray->line_start - HEIGHT / 2 + ray->line_h / 2) * step_pixel;
	y = ray->line_start;
	while (y < ray->line_end)
	{
		ray->tex_y = (int)text_pos % (HEIGHT);
		data->screen->addr[(y * WIDTH) + x]
			= text[(ray->tex_y * ray->text->width) + ray->tex_x];
		text_pos += step_pixel;
		y++;
	}
}

void	draw_ceiling(t_game_data *data, t_raycast *ray, int x, int *colors)
{
	int y;
	int color;

	color = create_trgb(0, colors[0], colors[1], colors[2]);
	y = 0;
	while (y < ray->line_start)
	{
		data->screen->addr[(y * WIDTH) + x] = color;
		y++;
	}
}

void	draw_floor(t_game_data *data, t_raycast *ray, int x, int *colors)
{
	int y;
	int color;

	color = create_trgb(0, colors[0], colors[1], colors[2]);
	y = ray->line_end;
	while (y < HEIGHT)
	{
		data->screen->addr[(y * WIDTH) + x] = color;
		y++;
	}
}
