/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarbay <jbarbay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 12:08:26 by jbarbay           #+#    #+#             */
/*   Updated: 2024/04/29 14:02:05 by jbarbay          ###   ########.fr       */
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

int	handle_input(int keysym, t_game_data *data)
{
	if (keysym == XK_Escape)
	{
		write(1, "Giving up so fast?\n", 19);
		exit_program(data);
	}
	else if (keysym == ARROW_UP || keysym == KEY_W)
		rerender(data, 0);
	else if (keysym == ARROW_DOWN || keysym == KEY_S)
		rerender(data, 1);
	else if (keysym == ARROW_LEFT)
		rerender(data, 2);
	else if (keysym == ARROW_RIGHT)
		rerender(data, 3);
	else if (keysym == KEY_A)
		rerender(data, 4);
	else if (keysym == KEY_D)
		rerender(data, 5);
	return (0);
}

t_img	*create_img(t_game_data *data, char *path, char *dir)
{
	t_img	*img;

	img = malloc(sizeof(t_img));
	if (!img)
		malloc_error(data);
	img->img_ptr = mlx_xpm_file_to_image(data->mlx_ptr, path, &(img->width), &(img->height));
	if (img->img_ptr == NULL)
		error_image(data, dir, img);
	img->addr = (int *)mlx_get_data_addr(img->img_ptr, &(img->bpp), &(img->len), &(img->ed));
	return (img);
}

void	create_textures(t_game_data *data)
{
	t_img		*screen;

	data->north_text = create_img(data, data->north_path, "north");
	data->south_text = create_img(data, data->south_path, "south");
	data->west_text = create_img(data, data->west_path, "west");
	data->east_text = create_img(data, data->east_path, "east");

	// Create screen image to add pixels to it later
	screen = malloc(sizeof(t_img));
	if (!screen)
		malloc_error(data);
	screen->img_ptr = mlx_new_image(data->mlx_ptr, WIDTH, HEIGHT);
	screen->addr = (int *)mlx_get_data_addr(screen->img_ptr, &(screen->bpp), &(screen->len), &(screen->ed));
	data->screen = screen;
}

void	start_cub(t_game_data *data)
{
	data->mlx_ptr = mlx_init();
	if (!data->mlx_ptr)
		malloc_error(data);
	create_textures(data);
	data->win_ptr = mlx_new_window(data->mlx_ptr, WIDTH, HEIGHT, "cub3d");
	if (!data->win_ptr)
		malloc_error(data);
	mlx_hook(data->win_ptr, 17, 0, exit_program, data);
	mlx_hook(data->win_ptr, 2, 1L<<0, handle_input, data);
	raycasting(data);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->screen->img_ptr, 0, 0);
	mlx_loop(data->mlx_ptr);
}

int	main(int argc, char *argv[])
{
	int			fd;
	t_game_data	*data;
	int			total_rows;

	check_args(argc);
	check_extension(argv[1], NULL, NULL, ".cub");
	fd = open_file(argv[1]);
	data = initialize_data_args(fd);
	get_textures_and_colors(data);
	total_rows = get_map(data);
	validate_map(data, total_rows);
	close(fd);
	start_cub(data);

	// test_helper(data);
	return (0);
}
