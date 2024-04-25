/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation_helpers.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarbay <jbarbay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 14:32:43 by jbarbay           #+#    #+#             */
/*   Updated: 2024/04/25 14:49:09 by jbarbay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

t_game_data	*initialize_data_args(int fd)
{
	t_game_data	*data;

	data = (t_game_data *)malloc(sizeof(t_game_data));
	if (!data)
		error_parsing("Memory allocation error", NULL, NULL, NULL);
	data->north_path = NULL;
	data->south_path = NULL;
	data->west_path = NULL;
	data->east_path = NULL;
	data->map = NULL;
	data->ceiling_color[0] = 266;
	data->floor_color[0] = 266;
	data->fd = fd;
	data->north_text = NULL;
	data->south_text = NULL;
	data->west_text = NULL;
	data->east_text = NULL;
	data->mlx_ptr = NULL;
	data->win_ptr = NULL;
	data->ray = NULL;
	data->screen = NULL;
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
	while (line)
	{
		free(line);
		line = NULL;
		line = get_next_line(data->fd);
	}
	if (data)
	{
		close(data->fd);
		free_data(data);
	}
	exit(1);
}

void	check_extension(char *file, char *line, t_game_data *data, char *ext)
{
	int	length;
	int	result;

	length = ft_strlen(file);
	file += (length - 4);
	result = ft_strncmp(file, ext, 4);
	if (result != 0 && ext[1] == 'x')
		error_parsing("Please provide textures in XPM format", NULL, line, data);
	else if (result != 0)
		error_parsing("Please provide the map in a .cub file", NULL, line, data);
}

