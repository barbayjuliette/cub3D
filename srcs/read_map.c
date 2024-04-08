/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarbay <jbarbay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 14:44:54 by jbarbay           #+#    #+#             */
/*   Updated: 2024/04/08 14:45:07 by jbarbay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	read_file(char **map, char *filename)
{
	int		fd;
	char	*buffer;
	int		bytes_read;

	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
	{
		free(*map);
		exit(1);
	}
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		error_file(*map, buffer, "Could not find file.\n");
	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
			error_file(buffer, *map, "Error reading file.\n");
		buffer[bytes_read] = '\0';
		ft_strjoin_2(map, buffer, 0, 0);
	}
	free(buffer);
	close(fd);
}

void	error_file(char *buffer, char *map, char *message)
{
	ft_putstr_fd("Error\n", 1);
	ft_putstr_fd(message, 1);
	free(buffer);
	free(map);
	exit(1);
}