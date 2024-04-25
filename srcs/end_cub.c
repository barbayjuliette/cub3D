/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_cub.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarbay <jbarbay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 14:49:51 by jbarbay           #+#    #+#             */
/*   Updated: 2024/04/25 14:56:32 by jbarbay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	free_textures(t_game_data *data)
{
	if (data->north_text)
	{
		mlx_destroy_image(data->mlx_ptr, data->north_text->img_ptr);
		free(data->north_text);
	}
	if (data->south_text)
	{
		mlx_destroy_image(data->mlx_ptr, data->south_text->img_ptr);
		free(data->south_text);
	}
	if (data->west_text)
	{
		mlx_destroy_image(data->mlx_ptr, data->west_text->img_ptr);
		free(data->west_text);
	}
	if (data->east_text)
	{
		mlx_destroy_image(data->mlx_ptr, data->east_text->img_ptr);
		free(data->east_text);
	}
}

int	exit_program(t_game_data *data)
{
	free_textures(data);
	if (data->ray)
		free(data->ray);
	if (data->screen)
	{
		mlx_destroy_image(data->mlx_ptr, data->screen->img_ptr);
		free(data->screen);
	}
	if (data->win_ptr)
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	if (data->mlx_ptr)
	{
		mlx_destroy_display(data->mlx_ptr);
		free(data->mlx_ptr);
	}
	free_data(data);
	exit(0);
}

void	malloc_error(t_game_data *data)
{
	ft_putstr_fd("Memory allocation error\n", 1);
	exit_program(data);
}

void	error_image(t_game_data *data, char *dir, t_img *texture)
{
	ft_putstr_fd("Error\n", 1);
	ft_putstr_fd("Could not load ", 1);
	ft_putstr_fd(dir, 1);
	ft_putendl_fd(" texture. Please provide a valid path", 1);
	free(texture);
	exit_program(data);
}
