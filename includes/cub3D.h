/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarbay <jbarbay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 12:10:03 by jbarbay           #+#    #+#             */
/*   Updated: 2024/04/19 15:23:34 by jbarbay          ###   ########.fr       */
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
	int		player_pos[2];
	char	player_dir;

} t_game_data;

// Map validation and reading

// Check values colors
int		parsing_error_colors(char *str);
int		check_color_format(char c, int i, int num);
void	get_colors(int *colors, char **args, char *line, t_game_data *data);

// Map validation
void	check_walls(int i, int j, int total_rows, t_game_data *data);
void	set_start_position(int	*pos, t_game_data *data, int i, int j);
void	validate_map(t_game_data *data, int total_rows);
char	**create_new_map(char **old_map, int total_rows, char *line, t_game_data *data);
int		get_map(int fd, t_game_data *data);

// Argument parsing
int		all_args_not_found(t_game_data *data);
char	*prepare_next_iteration(char *line, char **args, int fd, int first);
void	check_errors_argument(char **args, char *line, t_game_data *data);
void	check_identifier(t_game_data *data, char **args, char *line);
void	get_textures_and_colors(t_game_data *data);

// Get quoted path
int		is_quote(char **args);
char	**get_quoted_path(char *line, char **args);

// General utils
void	free_array(char **array);
int		array_len(char **arr);
char	*ft_strjoin_free(char *s1, char const *s2);
void	check_args(int argc);
void	print_map(char **map);
void	free_data(t_game_data *data);
int		open_file(char *filename);

// Validation helpers
t_game_data	*initialize_data_args(int fd);
void	error_parsing(char *message, char **array, char *line, t_game_data *data);
void	check_cub_file(char *filename);


#endif
