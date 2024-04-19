/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarbay <jbarbay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 13:43:46 by jbarbay           #+#    #+#             */
/*   Updated: 2024/04/19 12:16:31 by jbarbay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

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

int	array_len(char **arr)
{
	int		i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}

char	*ft_strjoin_free(char *s1, char const *s2)
{
	char	*string;
	int		i;
	int		j;

	i = 0;
	j = 0;
	string = (char *)malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (!string)
		return (NULL);
	while (s1[i])
	{
		string[j] = s1[i];
		i++;
		j++;
	}
	i = 0;
	while (s2[i])
	{
		string[j] = s2[i];
		i++;
		j++;
	}
	string[j] = '\0';
	free(s1);
	return (string);
}

void	check_args(int argc)
{
	if (argc != 2)
	{
		ft_putstr_fd("Error\nPlease provide a map in format in format *.cub\n", 1);
		exit(1);
	}
}

void	free_data(t_game_data *data)
{
	if (data->north_path)
		free(data->north_path);
	if (data->south_path)
		free(data->south_path);
	if (data->east_path)
		free(data->east_path);
	if (data->west_path)
		free(data->west_path);
	if (data->map)
		free_array(data->map);
	free(data);
}

void	print_map(char **map)
{
	int	i;

	i = 0;
	while (map[i])
	{
		ft_putendl_fd(map[i], 1);
		i++;
	}
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
