/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quoted_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarbay <jbarbay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 18:01:04 by jbarbay           #+#    #+#             */
/*   Updated: 2024/04/19 15:40:30 by jbarbay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

// [NO, "\"path_", "to_", "the_", "east""]
// [NO, path_ to_ the_ east]

int	is_quote(char **args)
{
	int	i;
	int	j;

	i = array_len(args) - 1;
	j = 0;
	if (args[1][0] != 34)
	{
		return (0);
	}
	while (args[i][j] != '\0')
		j++;
	if (args[i][j - 1] != 34)
		return (0);
	return (1);
}

char	**get_quoted_path(char *line, char **args)
{
	char	**new_args;
	char	*path;
	char	*id;

	if (array_len(args) == 2)
	{
		path = ft_substr(args[1], 1, ft_strlen(args[1]) - 2);
		free(args[1]);
		args[1] = path;
		return (args);
	}
	new_args = ft_split(line, 34);
	id = ft_strtrim(new_args[0], " ");
	free(new_args[0]);
	new_args[0] = id;
	free_array(args);
	return (new_args);
}
