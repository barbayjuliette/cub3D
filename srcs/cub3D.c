/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarbay <jbarbay@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 12:08:26 by jbarbay           #+#    #+#             */
/*   Updated: 2024/04/09 13:17:05 by jbarbay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	free_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

int	open_file(char *filename)
{
	int		fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		ft_putendl_fd("Error", 1);
		ft_putstr_fd("Could not open ", 1);
		ft_putendl_fd(filename, 1);
		exit(1);
	}
	return (fd);
}

t_game_data	*initialize_data_args(void)
{
	t_game_data	*data;

	data = (t_game_data *)malloc(sizeof(t_game_data));
	data->north_path = NULL;
	data->south_path = NULL;
	data->west_path = NULL;
	data->east_path = NULL;
	data->ceiling_color[0] = 266;
	data->floor_color[0] = 266;

	return (data);
}

int	all_args_not_found(t_game_data *data)
{
	// && data->floor_color[0] != 266 && data->ceiling_color[0] != 266
	if (data->north_path && data->south_path && data->east_path && data->west_path && data->floor_color[0] != 266 && data->ceiling_color[0] != 266)
		return (0);
	return (1);
}

int	array_len(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}

void	check_args(int argc)
{
	if (argc != 2)
	{
		ft_putstr_fd("Error\nPlease provide a map in format a map in format *.cub\n", 1);
		exit(1);
	}
}

void	error_parsing(char *message, int fd, char **array, char *line)
{
	ft_putendl_fd("Error", 1);
	ft_putendl_fd(message, 1);
	free_array(array);
	free(line);
	close(fd);
	exit(1);
}

void	parsing_error(char *str)
{
	ft_putendl_fd("Error", 1);
	ft_putendl_fd(str, 1);
	// FREE
	exit(1);
}

void	get_colors(int *colors, char *arg)
{
	int	num;
	int	i;
	int	index;

	i = 0;
	index = 0;
	while (i < 3)
	{
		num = 0;
		while (ft_isdigit(arg[index]))
		{
			num = num * 10 + arg[index] - '0';
			index++;
		}
		if (i < 2 && arg[index] != ',')
			parsing_error("Wrong format for color");
		if (i == 2 && arg[index] != '\n')
			parsing_error("Too many args after colors");
		if (num < 0 || num > 255)
			parsing_error("R,G,B colors must be in range [0,255]");
		colors[i] = num;
			index++;
		i++;
	}
}

int main(int argc, char *argv[])
{
	int		fd;
	char	*line;
	char	**split_line;
	t_game_data	*data;

	data = initialize_data_args();
	check_args(argc);
	fd = open_file(argv[1]);
	line = get_next_line(fd);
	while (line && all_args_not_found(data))
	{
		split_line = ft_split(line, ' ');
		if (!ft_strncmp(split_line[0], "1", 1)) // We found the map, but don't have all arguments yet
		{
			error_parsing("Please provide all arguments before the map", fd, split_line, line);
		}
		else if (array_len(split_line) == 1 &&  split_line[0][0] == '\n') // Empty line
		{
			free(line);
			line = get_next_line(fd);
			continue ;
		}
		else if (array_len(split_line) == 1) // No space between arguments
		{
			error_parsing("No space between arguments\nPlease provide arguments as follow: NO ./path_to_the_north_texture", fd, split_line, line);
		}
		else if (array_len(split_line) != 2) // Too many args on one line
		{
			error_parsing("Please provide arguments as follow: NO ./path_to_the_north_texture", fd, split_line, line);
		}
		else if (!ft_strncmp(split_line[0], "NO", 2))
		{
			data->north_path = split_line[1];
			free(split_line);
			free(split_line[0]);
		}
		else if (!ft_strncmp(split_line[0], "SO", 2))
		{
			data->south_path = split_line[1];
			free(split_line);
			free(split_line[0]);
		}
		else if (!ft_strncmp(split_line[0], "EA", 2))
		{
			data->east_path = split_line[1];
			free(split_line);
			free(split_line[0]);
		}
		else if (!ft_strncmp(split_line[0], "WE", 2))
		{
			data->west_path = split_line[1];
			free(split_line);
			free(split_line[0]);
		}
		else if (!ft_strncmp(split_line[0], "C", 1))
		{
			get_colors(data->ceiling_color, split_line[1]);
		}
		else if (!ft_strncmp(split_line[0], "F", 1))
		{
			get_colors(data->floor_color, split_line[1]);
		}
		else
		{
			error_parsing("Parsing error. Please only provide requested arguments", fd, split_line, line);
		}
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	printf("Path found for north: %s\n", data->north_path);
	printf("Path found for south: %s\n", data->south_path);
	printf("Path found for east: %s\n", data->east_path);
	printf("Path found for west: %s\n", data->west_path);
	printf("Colors floor: [%i, %i, %i]\n", data->floor_color[0], data->floor_color[1], data->floor_color[2]);
	printf("Colors ceiling: [%i, %i, %i]\n", data->ceiling_color[0], data->ceiling_color[1], data->ceiling_color[2]);
	close(fd);
	return 0;
}
