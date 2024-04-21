/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarbay <jbarbay@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 12:08:26 by jbarbay           #+#    #+#             */
/*   Updated: 2024/04/21 11:07:47 by jbarbay          ###   ########.fr       */
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
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	mlx_destroy_display(data->mlx_ptr);
	free(data->mlx_ptr);
	data->mlx_ptr = NULL;
	free_array(data->map);
	exit(0);
}

int	handle_input(int keysym, t_game_data *data)
{
	if (keysym == XK_Escape)
	{
		write(1, "Giving up so fast?\n", 19);
		exit_program(data);
	}
	return (0);
}

void	start_cub(t_game_data *data)
{
	data->mlx_ptr = mlx_init();
	if (!data->mlx_ptr)
		exit(1); // End and free everything
	data->win_ptr = mlx_new_window(data->mlx_ptr, WIDTH, HEIGHT, "cub3d");
	if (!data->win_ptr)
	{
		mlx_destroy_display(data->mlx_ptr);
		free(data->mlx_ptr);
		exit(1); // Free everything else
	}
	mlx_hook(data->win_ptr, 17, 0, exit_program, data);
	mlx_key_hook(data->win_ptr, handle_input, data);
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
