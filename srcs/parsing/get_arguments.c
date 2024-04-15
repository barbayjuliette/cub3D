/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_arguments.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarbay <jbarbay@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 18:09:13 by jbarbay           #+#    #+#             */
/*   Updated: 2024/04/15 18:02:49 by jbarbay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

int	all_args_not_found(t_game_data *data)
{
	if (data->north_path && data->south_path && data->east_path
		&& data->west_path && data->floor_color[0] != 266
		&& data->ceiling_color[0] != 266)
		return (0);
	return (1);
}

char	*prepare_next_iteration(char *line, char **args, int fd)
{
	free_array(args);
	free(line);
	return (get_next_line(fd));
}

// 1. We found the map, but don't have all arguments yet
// 2. No space between arguments
// 3. Too many args on one line

// If new line, ignore, just go the next iteration

void	check_errors_argument(char **args, char *line, t_game_data *data)
{
	int	len;

	len = array_len(args);
	if (!ft_strncmp(args[0], "1", 1))
		error_parsing("Provide all arguments before the map", args, line, data);
	else if (len == 1 && args[0][0] != '\n')
	{
		error_parsing("No space between arguments\n \
Please provide arguments as follow: NO ./path_to_the_north_texture", \
		args, line, data);
	}
	else if (len != 2 && args[0][0] != '\n' && is_quote(args) == 0)
	{
		error_parsing("Please provide arguments as follow 444: \
NO ./path_to_the_north_texture \nF 220,100,0", args, line, data);
	}
}

void	check_identifier(t_game_data *data, char **args, char *line)
{
	if (!ft_strncmp(args[0], "NO", 3))
		data->north_path = ft_substr(args[1], 0, ft_strlen(args[1]) - 1);
	else if (!ft_strncmp(args[0], "SO", 3))
		data->south_path = ft_substr(args[1], 0, ft_strlen(args[1]) - 1);
	else if (!ft_strncmp(args[0], "EA", 3))
		data->east_path = ft_substr(args[1], 0, ft_strlen(args[1]) - 1);
	else if (!ft_strncmp(args[0], "WE", 3))
		data->west_path = ft_substr(args[1], 0, ft_strlen(args[1]) - 1);
	else if (!ft_strncmp(args[0], "C", 2))
		get_colors(data->ceiling_color, args, line, data);
	else if (!ft_strncmp(args[0], "F", 2))
		get_colors(data->floor_color, args, line, data);
	else if (args[0][0] != '\n')
		error_parsing("Only provide requested arguments", args, line, data);
}

void	get_textures_and_colors(int fd, t_game_data *data)
{
	char		*line;
	char		**args;

	line = get_next_line(fd);
	while (line && all_args_not_found(data))
	{
		args = ft_split(line, ' ');
		check_errors_argument(args, line, data);
		if (array_len(args) > 1 && is_quote(args))
			args = get_quoted_path(line, args);
		check_identifier(data, args, line);
		line = prepare_next_iteration(line, args, fd);
	}
	free(line);
}
