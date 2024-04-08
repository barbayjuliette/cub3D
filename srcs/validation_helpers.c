/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation_helpers.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarbay <jbarbay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 14:32:43 by jbarbay           #+#    #+#             */
/*   Updated: 2024/04/08 14:33:29 by jbarbay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	ft_strjoin_2(char **map, char *buffer, int i, int j)
{
	char	*string;

	string = (char *)malloc((ft_strlen(*map) + ft_strlen(buffer) + 1)
			* sizeof(char));
	if (!string)
		return (1);
	while ((*map)[i])
	{
		string[j] = (*map)[i];
		i++;
		j++;
	}
	i = 0;
	while (buffer[i])
	{
		string[j] = buffer[i];
		i++;
		j++;
	}
	string[j] = '\0';
	free(*map);
	*map = string;
	return (0);
}
