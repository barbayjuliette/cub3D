/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarbay <jbarbay@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 12:08:26 by jbarbay           #+#    #+#             */
/*   Updated: 2024/04/10 22:24:18 by jbarbay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	all_args_not_found(t_game_data *data)
{
	if (data->north_path && data->south_path && data->east_path && data->west_path && data->floor_color[0] != 266 && data->ceiling_color[0] != 266)
		return (0);
	return (1);
}

char	*prepare_next_iteration(char *line, char **split_line, int fd)
{
	free_array(split_line);
	free(line);
	return (get_next_line(fd));
}

void	check_errors_argument(char **split_line, char *line, t_game_data *data)
{
	if (!ft_strncmp(split_line[0], "1", 1)) // We found the map, but don't have all arguments yet
		error_parsing("Please provide all arguments before the map", split_line, line, data);
	else if (array_len(split_line) == 1 && split_line[0][0] != '\n') // No space between arguments
		error_parsing("No space between arguments\nPlease provide arguments as follow: NO ./path_to_the_north_texture", split_line, line, data);
	else if (array_len(split_line) != 2 && split_line[0][0] != '\n') // Too many args on one line
		error_parsing("Please provide arguments as follow: \nNO ./path_to_the_north_texture \nF 220,100,0", split_line, line, data);
}

void	get_textures_and_colors(int fd, t_game_data *data)
{
	char		*line;
	char		**split_line;

	line = get_next_line(fd);
	while (line && all_args_not_found(data))
	{
		split_line = ft_split(line, ' ');
		check_errors_argument(split_line, line, data);
		if (!ft_strncmp(split_line[0], "NO", 3))
			data->north_path = ft_substr(split_line[1], 0, ft_strlen(split_line[1]) - 1);
		else if (!ft_strncmp(split_line[0], "SO", 3))
			data->south_path = ft_substr(split_line[1], 0, ft_strlen(split_line[1]) - 1);
		else if (!ft_strncmp(split_line[0], "EA", 3))
			data->east_path = ft_substr(split_line[1], 0, ft_strlen(split_line[1]) - 1);
		else if (!ft_strncmp(split_line[0], "WE", 3))
			data->west_path = ft_substr(split_line[1], 0, ft_strlen(split_line[1]) - 1);
		else if (!ft_strncmp(split_line[0], "C", 2))
			get_colors(data->ceiling_color, split_line, line, data);
		else if (!ft_strncmp(split_line[0], "F", 2))
			get_colors(data->floor_color, split_line, line, data);
		else if (split_line[0][0] != '\n')// If new line, ignore, just go the next iteration
			error_parsing("Parsing error. Please only provide requested arguments", split_line, line, data);
		line = prepare_next_iteration(line, split_line, fd);
	}
	free(line);
}

char	**create_new_map(char **old_map, int total_rows, char *line)
{
	char	**new_map;
	int		i;

	i = 0;
	new_map = (char **)malloc(sizeof(char *) * (total_rows + 1));
	if (!new_map)
		return (NULL); // MALLOC ERROR
	while (old_map[i])
	{
		new_map[i] = old_map[i];
		i++;
	}
	new_map[i] = line;
	new_map[i + 1] = NULL;
	free(old_map);
	return (new_map);
}

void	get_map(int fd, t_game_data *data)
{
	int	total_rows;
	char	**map;
	char	*line;

	total_rows = 0;
	line = get_next_line(fd);
	map = (char **)malloc(sizeof(char *) * (total_rows + 1));

	if (!map)
		return ; // MALLOC ERROR
	map[0] = NULL;

	while (line)
	{
		total_rows++;
		map = create_new_map(map, total_rows, line);
		line = get_next_line(fd);
	}
	if (total_rows == 0)
		return ; // + ERROR No map found
	data->map = map;
}

void	print_map(char **map)
{
	int	i;

	i = 0;
	while (map[i])
	{
		ft_putstr_fd(map[i], 1);
		i++;
	}
}

int	main(int argc, char *argv[])
{
	int			fd;
	t_game_data	*data;

	fd = open_file(argv[1]);
	data = initialize_data_args(fd);
	check_args(argc);
	get_textures_and_colors(fd, data);
	get_map(fd, data);
	close(fd);

	printf("Path found for north: %s\n", data->north_path);
	printf("Path found for south: %s\n", data->south_path);
	printf("Path found for east: %s\n", data->east_path);
	printf("Path found for west: %s\n", data->west_path);
	printf("Colors floor: [%i, %i, %i]\n", data->floor_color[0], data->floor_color[1], data->floor_color[2]);
	printf("Colors ceiling: [%i, %i, %i]\n", data->ceiling_color[0], data->ceiling_color[1], data->ceiling_color[2]);
	print_map(data->map);
	return (0);
}
