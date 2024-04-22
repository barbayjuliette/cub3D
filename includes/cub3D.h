/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarbay <jbarbay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 12:10:03 by jbarbay           #+#    #+#             */
/*   Updated: 2024/04/22 17:04:55 by jbarbay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

#include <stdio.h>

#define BUFFER_SIZE 1
#define HEIGHT 480
#define WIDTH 640

#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <mlx.h>
#include <X11/keysym.h>
#include "../libft/libft.h"
#include "../libft/gnl/get_next_line.h"

typedef struct s_img
{
	void	*img_ptr;
	char	*addr;
	int		height;
	int		width;
	int		bpp;
	int		endian;
	int		line_len;
}	t_img;

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
	void	*mlx_ptr;
	void	*win_ptr;
	t_img	*north_text;
	t_img	*south_text;
	t_img	*east_text;
	t_img	*west_text;

} t_game_data;

typedef struct s_raycast
{
	double		position_x;
	double		position_y;
	double		camera_plane_x;
	double		camera_plane_y;
	double		direction_x;
	double		direction_y;
	double		camera_x;
	double		ray_dir_x;
	double		ray_dir_y;
	int			map_x;
	int			map_y;
	double		side_dist_x;
	double		side_dist_y;
	double		delta_dist_x;
	double		delta_dist_y;
	double		perp_wall_dist;
	int			step_x;
	int			step_y;
	int			hit;
	int			side; // NS hit (y-side): 1, EW wall hit (x-side): 0
	int			line_height;
} t_raycast;

typedef  struct  s_vert_line
{
	int  x; //the x coordinate of line relative to screen
	int  y; //the current pixel index of the line (along y axis)
	int  y0; //y start index of drawing texture
	int  y1; //y end index of drawing texture
	int  tex_x; //x coordinate of texture to draw
	int  tex_y; //y coordinate of texture to draw
} t_vert_line;


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
int		get_map(t_game_data *data);

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

// Raycasting
void	raycasting(t_game_data *data);
t_raycast	*initialize_raycasting_data(t_game_data *data);


#endif
