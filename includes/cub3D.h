/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarbay <jbarbay@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 12:10:03 by jbarbay           #+#    #+#             */
/*   Updated: 2024/04/09 13:46:02 by jbarbay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

#include <stdio.h>

#define BUFFER_SIZE 1
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include "../libft/libft.h"
#include "../libft/gnl/get_next_line.h"

typedef struct s_game_data
{
	char	*north_path;
	char	*south_path;
	char	*west_path;
	char	*east_path;
	int		floor_color[3];
	int		ceiling_color[3];
	char	**map;

} t_game_data;

// Map validation and reading

int	parsing_error_colors(char *str);
int	check_color_format(char c, int i, int num);
int	get_colors(int *colors, char *arg);

void	free_array(char **array);
int		array_len(char **arr);
void	check_args(int argc);
int		open_file(char *filename);


#endif
