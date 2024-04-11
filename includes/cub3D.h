/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarbay <jbarbay@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 12:10:03 by jbarbay           #+#    #+#             */
/*   Updated: 2024/04/11 18:22:35 by jbarbay          ###   ########.fr       */
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
	int		fd;

} t_game_data;

// Map validation and reading

int		parsing_error_colors(char *str);
int		check_color_format(char c, int i, int num);
void	get_colors(int *colors, char **args, char *line, t_game_data *data);

void	free_array(char **array);
int		array_len(char **arr);
void	check_args(int argc);
int		open_file(char *filename);
void	print_map(char **map);

void	free_data(t_game_data *data);

void	error_parsing(char *message, char **array, char *line, t_game_data *data);
t_game_data	*initialize_data_args(int fd);

int		all_args_not_found(t_game_data *data);
char	*prepare_next_iteration(char *line, char **args, int fd);
void	check_errors_argument(char **args, char *line, t_game_data *data);
void	get_textures_and_colors(int fd, t_game_data *data);

int		get_map(int fd, t_game_data *data);
void	validate_map(t_game_data *data, int total_rows);
void	check_walls(int i, int j, int total_rows, t_game_data *data);
void	check_cub_file(char *filename);
char	**create_new_map(char **old_map, int total_rows, char *line, t_game_data *data);


#endif
