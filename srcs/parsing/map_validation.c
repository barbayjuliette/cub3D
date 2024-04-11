/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarbay <jbarbay@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 17:40:17 by jbarbay           #+#    #+#             */
/*   Updated: 2024/04/11 18:24:34 by jbarbay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void	check_walls(int i, int j, int total_rows, t_game_data *data)
{
	if ((i == 0 || i == total_rows - 1) && data->map[i][j] != '1')
			error_parsing("Map must be enclosed by walls 1", NULL, NULL, data);
	else if (j == 0 && data->map[i][j] != '1')
		error_parsing("Map must be enclosed by walls 2", NULL, NULL, data);
	else if (data->map[i][j + 1] && data->map[i][j + 1] == '\n' && data->map[i][j] != '1')
		error_parsing("Map must be enclosed by walls 3", NULL, NULL, data);
	else if (!data->map[i][j + 1] && data->map[i][j] != '1')
		error_parsing("Map must be enclosed by walls 4", NULL, NULL, data);
}

void	validate_map(t_game_data *data, int total_rows)
{
	int	i;
	int	j;
	int	pos;

	i = 0;
	pos = 0;
	while (data->map[i])
	{
		j = 0;
		while (data->map[i][j])
		{
			if (data->map[i][j] == ' ')
				data->map[i][j] = '1';
			check_walls(i, j, total_rows, data);
			if (!ft_strrchr("01NSWE\n", data->map[i][j]))
				error_parsing("Map must only contain characters 01NSWE", NULL, NULL, data);
			if (data->map[i][j] == 'N' || data->map[i][j] == 'S' || data->map[i][j] == 'W' || data->map[i][j] == 'E')
				pos++;
			if (pos > 1)
				error_parsing("Position only one starting player", NULL, NULL, data);
			j++;
		}
		i++;
	}
}

char	**create_new_map(char **old_map, int total_rows, char *line, t_game_data *data)
{
	char	**new_map;
	int		i;

	i = 0;
	new_map = (char **)malloc(sizeof(char *) * (total_rows + 1));
	if (!new_map)
		error_parsing("Malloc error", NULL, NULL, data);
	while (old_map[i])
	{
		new_map[i] = old_map[i];
		i++;
	}
	new_map[i] = ft_strtrim(line, "\n");
	free(line);
	new_map[i + 1] = NULL;
	free(old_map);
	return (new_map);
}

int	get_map(int fd, t_game_data *data)
{
	int	total_rows;
	char	**map;
	char	*line;

	total_rows = 0;
	line = get_next_line(fd);
	map = (char **)malloc(sizeof(char *) * (total_rows + 1));
	if (!map)
		error_parsing("Malloc error", NULL, NULL, data);
	map[0] = NULL;
	while (line)
	{
		total_rows++;
		map = create_new_map(map, total_rows, line, data);
		line = get_next_line(fd);
	}
	if (total_rows == 0)
		error_parsing("No map found", NULL, NULL, data);
	data->map = map;
	return (total_rows);
}
