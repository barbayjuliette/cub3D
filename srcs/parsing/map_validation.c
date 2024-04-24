/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarbay <jbarbay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 17:40:17 by jbarbay           #+#    #+#             */
/*   Updated: 2024/04/22 12:15:49 by jbarbay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

int	square_is_empty(int i, int j, t_game_data *data)
{
	int	len;

	len = ft_strlen(data->map[i]) - 1;
	if (j > len) // above is empty
		return (1);
	return (0);
}

void	check_walls(int i, int j, int total_rows, t_game_data *data)
{
	if ((i == 0 || i == total_rows - 1) && data->map[i][j] != '1')
		error_parsing("Map must be enclosed by walls 1", NULL, NULL, data);
	else if (i > 0 && square_is_empty(i - 1, j, data) && data->map[i][j] != '1')
		error_parsing("Map must be enclosed by walls 11", NULL, NULL, data);
	else if (data->map[i + 1] && square_is_empty(i + 1, j, data) && data->map[i][j] != '1')
		error_parsing("Map must be enclosed by walls 22", NULL, NULL, data);
	else if (j == 0 && data->map[i][j] != '1')
		error_parsing("Map must be enclosed by walls 2", NULL, NULL, data);
	else if (data->map[i][j + 1] && data->map[i][j + 1] == '\n' && data->map[i][j] != '1')
		error_parsing("Map must be enclosed by walls 3", NULL, NULL, data);
	else if (!data->map[i][j + 1] && data->map[i][j] != '1')
		error_parsing("Map must be enclosed by walls 4", NULL, NULL, data);
}

void	set_start_position(int	*pos, t_game_data *data, int i, int j)
{
	if (*pos > 0)
		error_parsing("Position only one starting player", NULL, NULL, data);
	data->player_dir = data->map[i][j];
	data->player_pos[0] = j;
	data->player_pos[1] = i;
	(*pos)++;
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
			if (data->map[i][j] == 'N' || data->map[i][j] == 'S'
			|| data->map[i][j] == 'W' || data->map[i][j] == 'E')
				set_start_position(&pos, data, i, j);
			j++;
		}
		i++;
	}
	if (pos == 0)
		error_parsing("You must position the starting player", NULL, NULL, data);
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

int	get_map(t_game_data *data)
{
	int		total_rows;
	char	**map;
	char	*line;

	total_rows = 0;
	line = get_next_line(data->fd);
	map = (char **)malloc(sizeof(char *) * (total_rows + 1));
	if (!map)
		error_parsing("Malloc error", NULL, NULL, data);
	map[0] = NULL;
	while (line)
	{
		if (ft_strncmp(line, "\n", 2) == 0)
			break ;
		total_rows++;
		map = create_new_map(map, total_rows, line, data);
		line = get_next_line(data->fd);
	}
	// free(line);
	if (total_rows == 0)
		error_parsing("No map found", map, NULL, data);
	data->map = map;
	return (total_rows);
}
