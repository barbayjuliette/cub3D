/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rerender.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarbay <jbarbay@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 16:02:49 by akolgano          #+#    #+#             */
/*   Updated: 2024/05/09 15:21:03 by jbarbay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

t_raycast	*recalculate_raycasting_data(t_game_data *data, int mode)
{
	t_raycast	*ray;

	ray = (t_raycast *)malloc(sizeof(t_raycast));
	if (!ray)
		malloc_error(data);
	ray = data->ray;
	if (mode == 0)
		return (move_forward(data));
	else if (mode == 1)
		return (move_back(data));
	else if (mode == 3)
		return (rotate_right(data));
	else if (mode == 2)
		return (rotate_left(data));
	else if (mode == 4)
		return (move_left(data));
	else if (mode == 5)
		return (move_right(data));
	return (ray);
}

int	rerender(t_game_data *data, int mode)
{
	mlx_destroy_image(data->mlx_ptr, data->screen->img_ptr);
	free(data->screen);
	data->screen = malloc(sizeof(t_img));
	if (!data->screen)
		malloc_error(data);
	data->screen->img_ptr = mlx_new_image(data->mlx_ptr, WIDTH, HEIGHT);
	data->screen->addr = (int *)mlx_get_data_addr(data->screen->img_ptr,
			&(data->screen->bpp), &(data->screen->len), &(data->screen->ed));
	raycasting(data, mode);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
		data->screen->img_ptr, 0, 0);
	return (0);
}
