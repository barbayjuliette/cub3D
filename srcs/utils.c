/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarbay <jbarbay@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 13:43:46 by jbarbay           #+#    #+#             */
/*   Updated: 2024/04/09 13:45:00 by jbarbay          ###   ########.fr       */
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
