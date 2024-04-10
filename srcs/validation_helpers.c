/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation_helpers.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarbay <jbarbay@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 14:32:43 by jbarbay           #+#    #+#             */
/*   Updated: 2024/04/10 22:44:59 by jbarbay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

t_game_data	*initialize_data_args(int fd)
{
	t_game_data	*data;

	data = (t_game_data *)malloc(sizeof(t_game_data));
	data->north_path = NULL;
	data->south_path = NULL;
	data->west_path = NULL;
	data->east_path = NULL;
	data->map = NULL;
	data->ceiling_color[0] = 266;
	data->floor_color[0] = 266;
	data->fd = fd;
	return (data);
}

void	error_parsing(char *message, char **array, char *line, t_game_data *data)
{
	if (message)
	{
		ft_putendl_fd("Error", 1);
		ft_putendl_fd(message, 1);
	}
	if (array)
		free_array(array);
	if (line)
		free(line);
	if (data)
	{
		close(data->fd);
		free_data(data);
		if (data->map)
			free_array(data->map);
	}
	exit(1);
}
