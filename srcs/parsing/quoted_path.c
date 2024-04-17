/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quoted_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarbay <jbarbay@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 18:01:04 by jbarbay           #+#    #+#             */
/*   Updated: 2024/04/15 18:02:47 by jbarbay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

// [NO, "\"path_", "to_", "the_", "east""]
// [NO, path_to_the_east]

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
	while (args[i][j] != '\n')
		j++;
	if (args[i][j - 1] != 34)
		return (0);
	return (1);
}

char	**get_quoted_path(char *line, char **args)
{
	char	**new_args;
	char	*path;
	int		i;

	i = 2;
	if (array_len(args) == 2)
	{
		path = ft_substr(args[1], 1, ft_strlen(args[1]) - 2);
		free(args[1]);
		args[1] = path;
		return (args);
	}
	path = ft_strjoin(args[1], args[2]);
	new_args = (char **)malloc(sizeof(char *) * (2 + 1));
	if (!new_args)
		return (NULL);
	while (args[++i])
		path = ft_strjoin_free(path, args[i]);
	new_args[0] = ft_strdup(args[0]);
	new_args[1] = ft_substr(path, 1, ft_strlen(path) - 2);
	new_args[2] = NULL;
	free(path);
	free_array(args);
	return (new_args);
}
