/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarbay <jbarbay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 12:08:26 by jbarbay           #+#    #+#             */
/*   Updated: 2024/04/08 14:45:15 by jbarbay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int main(int argc, char *argv[])
{
	char	*map;

	if (argc != 2)
	{
		ft_putstr_fd("Error\nPlease provide a map in format a map in format *.cub\n", 1);
		return (1);
	}

	map = (char *)malloc(sizeof(char));
	if (!map)
		exit(1);
	map[0] = '\0';
	read_file(&map, argv[1]);
	get_paths_textures(map);
	return 0;
}