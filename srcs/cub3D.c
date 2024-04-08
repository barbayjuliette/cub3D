/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarbay <jbarbay@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 12:08:26 by jbarbay           #+#    #+#             */
/*   Updated: 2024/04/08 22:42:11 by jbarbay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

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
	if (data->north_path && data->south_path && data->east_path && data->west_path)
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

int main(int argc, char *argv[])
{
	int		fd;
	char	*line;
	char	**split_line;
	t_game_data	*data;

	data = initialize_data_args();
	if (argc != 2)
	{
		ft_putstr_fd("Error\nPlease provide a map in format a map in format *.cub\n", 1);
		return (1);
	}
	fd = open_file(argv[1]);
	line = get_next_line(fd);
	while (line && all_args_not_found(data))
	{
		// printf("line: %s", line);
		split_line = ft_split(line, ' ');
		if (!ft_strncmp(split_line[0], "1", 1))
		{
			ft_putendl_fd("Error", 1);
			ft_putendl_fd("Please provide all arguments before the map", 1);
			free(split_line); // Free the whole array one by one!!!!
			close(fd);
			return (1);
		}
		else if (array_len(split_line) == 1 &&  split_line[0][0] == '\n') // Empty line
		{
			free(line);
			line = get_next_line(fd);
			continue ;
		}
		else if (array_len(split_line) == 1) // No space between arguments
		{
			ft_putendl_fd("Error", 1);
			ft_putendl_fd("No space", 1);
			// printf("Length: %i\n", array_len(split_line));
			// printf("split_line[0]: %s", split_line[0]);
			ft_putendl_fd("Please provide arguments as follow: NO ./path_to_the_north_texture", 1);
			free(split_line); // Free the whole array one by one!!!!
			close(fd);
			return (1);
		}
		else if (array_len(split_line) != 2)
		{
			ft_putendl_fd("Error", 1);
			printf("Length: %i\n", array_len(split_line));
			printf("split_line[0]: %s", split_line[0]);
			ft_putendl_fd("Please provide arguments as follow: NO ./path_to_the_north_texture", 1);
			free(split_line); // Free the whole array one by one!!!!
			close(fd);
			return (1);
		}
		else if (!ft_strncmp(split_line[0], "NO", 2))
		{
			data->north_path = split_line[1];
			// free(split_line);
			// free(split_line[0]);
		}
		else if (!ft_strncmp(split_line[0], "SO", 2))
		{
			data->south_path = split_line[1];
			// free(split_line);
			// free(split_line[0]);
		}
		else if (!ft_strncmp(split_line[0], "EA", 2))
		{
			data->east_path = split_line[1];
			// free(split_line);
			// free(split_line[0]);
		}
		else if (!ft_strncmp(split_line[0], "WE", 2))
		{
			data->west_path = split_line[1];
			// free(split_line);
			// free(split_line[0]);
		}
		else
		{
			free(split_line);
			free(split_line[0]);
			free(split_line[1]);
		}
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	printf("Path found for north:\n%s\n", data->north_path);
	printf("Path found for south:\n%s\n", data->south_path);
	printf("Path found for east:\n%s\n", data->east_path);
	printf("Path found for west:\n%s\n", data->west_path);
	close(fd);
	return 0;
}
