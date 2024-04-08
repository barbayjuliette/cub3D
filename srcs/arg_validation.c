/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarbay <jbarbay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 12:11:19 by jbarbay           #+#    #+#             */
/*   Updated: 2024/04/08 17:00:51 by jbarbay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"


char	*get_path_texture(char *map, int *index)
{
	int		j;
	int		len;
	char	*path;

	j = 0;
	len = 0;
	while (map[*index] == ' ')
		(*index)++;
	while (map[*index] && map[*index] != ' ' && map[*index] != '\n')
	{
		(*index)++;
		len++;
	}
	path = (char *)malloc(sizeof(char) * (len + 1));
	if (!path)
		printf("malloc error\n");
	*index = *index - len;
	while (j < len)
	{
		path[j] = map[*index];
		(*index)++;
		j++;
	}
	(*index)++;
	path[j] = '\0';
	return (path);
}

t_game_data	*get_paths_textures(char *map)
{
	t_game_data	*data;
	int	i;

	i = 0;
	// data = NULL;
	data = (t_game_data *)malloc(sizeof(t_game_data));
	data->north_path = NULL;
	data->south_path = NULL;
	data->west_path = NULL;
	data->east_path = NULL;
	data->ceiling_color[0] = 266;
	data->floor_color[0] = 266;

	while (map[i])
	{
		if (data->north_path && data->south_path && data->east_path && data->west_path && data->floor_color[0] != 266 && data->ceiling_color[0] != 266)
			break ;
		else if (!ft_strncmp(map + i, "NO", 2) && !data->north_path)
			data->north_path = get_path_texture(map + 2, &i);
		else if (!ft_strncmp(map + i, "SO", 2) && !data->south_path)
			data->south_path = get_path_texture(map + 2, &i);
		else if (!ft_strncmp(map + i, "EA", 2) && !data->east_path)
			data->east_path = get_path_texture(map + 2, &i);
		else if (!ft_strncmp(map + i, "WE", 2) && !data->west_path)
			data->west_path = get_path_texture(map + 2, &i);
		else
			i++;
	}
	printf("Path found for north:\n%s\n", data->north_path);
	printf("Path found for south:\n%s\n", data->south_path);
	printf("Path found for east:\n%s\n", data->east_path);
	printf("Path found for west:\n%s\n", data->west_path);
	// printf("This is the map I got:\n%s", map);
	return (data);

}