/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarbay <jbarbay@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 12:08:26 by jbarbay           #+#    #+#             */
/*   Updated: 2024/04/24 10:37:42 by jbarbay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	test_helper(t_game_data *data)
{
	printf("Path found for north: %s\n", data->north_path);
	printf("Path found for south: %s\n", data->south_path);
	printf("Path found for east: %s\n", data->east_path);
	printf("Path found for west: %s\n", data->west_path);
	printf("Colors floor: [%i, %i, %i]\n", data->floor_color[0], data->floor_color[1], data->floor_color[2]);
	printf("Colors ceiling: [%i, %i, %i]\n", data->ceiling_color[0], data->ceiling_color[1], data->ceiling_color[2]);
	printf("Player direction: %c\n", data->player_dir);
	printf("Player position: [%i, %i]\n", data->player_pos[0], data->player_pos[1]);
	print_map(data->map);
}

int	exit_program(t_game_data *data)
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
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	// mlx_destroy_display(data->mlx_ptr);
	free(data->mlx_ptr);
	free_data(data);
	exit(0);
}

int	handle_input(int keysym, t_game_data *data)
{
	if (keysym == 101)
	{
		write(1, "Giving up so fast?\n", 19);
		exit_program(data);
	}
	return (0);
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

t_img	*create_img(t_game_data *data, char *path, char *dir)
{
	t_img	*texture;

	texture = malloc(sizeof(t_img));
	if (!texture)
	{
		ft_putendl_fd("malloc error", 1);
		exit(1);
	}
	texture->img_ptr = mlx_xpm_file_to_image(data->mlx_ptr, path, &(texture->width), &(texture->height));
	texture->addr = (int *)mlx_get_data_addr(texture->img_ptr, &(texture->bpp), &(texture->line_len), &(texture->endian));
	if (texture->img_ptr == NULL)
		error_image(data, dir, texture);
	return (texture);
}

void	create_textures(t_game_data *data)
{
	t_img		*screen;

	data->north_text = create_img(data, data->north_path, "north");
	data->south_text = create_img(data, data->south_path, "south");
	data->west_text = create_img(data, data->west_path, "west");
	data->east_text = create_img(data, data->east_path, "east");
	// mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->north_text->img_ptr, 10, 10);

	// Create screen image to add pixels to it later
	screen = malloc(sizeof(t_img));
	screen->img_ptr = mlx_new_image(data->mlx_ptr, WIDTH, HEIGHT);
	screen->addr = (int *)mlx_get_data_addr(screen->img_ptr, &(screen->bpp), &(screen->line_len), &(screen->endian));
	data->screen = screen;
}

void	start_cub(t_game_data *data)
{
	data->mlx_ptr = mlx_init();
	if (!data->mlx_ptr)
		exit(1); // End and free everything
	data->win_ptr = mlx_new_window(data->mlx_ptr, WIDTH, HEIGHT, "cub3d");
	if (!data->win_ptr)
	{
		// mlx_destroy_display(data->mlx_ptr);
		free(data->mlx_ptr);
		exit(1); // Free everything else
	}
	create_textures(data);
	mlx_hook(data->win_ptr, 17, 0, exit_program, data);
	mlx_key_hook(data->win_ptr, handle_input, data);
	raycasting(data);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->screen->img_ptr, 0, 0);
	mlx_loop(data->mlx_ptr);
}

int	main(int argc, char *argv[])
{
	int			fd;
	t_game_data	*data;
	int			total_rows;

	check_cub_file(argv[1]);
	fd = open_file(argv[1]);
	data = initialize_data_args(fd);
	check_args(argc);
	get_textures_and_colors(data);
	total_rows = get_map(data);
	validate_map(data, total_rows);
	close(fd);
	start_cub(data);

	// test_helper(data);
	return (0);
}
