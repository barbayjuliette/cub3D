#include "../../includes/cub3D.h"

t_raycast	*recalculate_raycasting_data(t_game_data *data)
{
	t_raycast	*ray;

	ray = (t_raycast *)malloc(sizeof(t_raycast));
	if (!ray)
		malloc_error(data);
	ray = data->ray;
	int moveSpeed = 1;
	if (data->flag == 0)
	{
			ray->position_x += ray->direction_x  * moveSpeed;
			ray->position_y += ray->direction_y * moveSpeed;
	}
	
	if (data->flag == 1)
	{
		ray->position_x -= ray->direction_x * moveSpeed;
		ray->position_y -= ray->direction_y* moveSpeed;
	}
	if (data->flag == 3)
	{
		int rotSpeed = 1;
		double oldDirX = ray->direction_x;
     	ray->direction_x = ray->direction_x * cos(rotSpeed) - ray->direction_y * sin(rotSpeed);
      	ray->direction_y = oldDirX * sin(rotSpeed) + ray->direction_y * cos(rotSpeed);
      	double oldPlaneX = ray->camera_plane_x ;
      	ray->camera_plane_x = ray->camera_plane_x * cos(rotSpeed) - ray->camera_plane_y * sin(rotSpeed);
      	ray->camera_plane_y = oldPlaneX * sin(rotSpeed) + ray->camera_plane_y * cos(rotSpeed);
	}
	if (data->flag == 2)
	{
		int rotSpeed = 1;
		double oldDirX = ray->direction_x;
     	ray->direction_x = ray->direction_x * cos(-rotSpeed) - ray->direction_y * sin(-rotSpeed);
      	ray->direction_y = oldDirX * sin(-rotSpeed) + ray->direction_y * cos(-rotSpeed);
      	double oldPlaneX = ray->camera_plane_x ;
      	ray->camera_plane_x = ray->camera_plane_x * cos(-rotSpeed) - ray->camera_plane_y * sin(-rotSpeed);
      	ray->camera_plane_y = oldPlaneX * sin(-rotSpeed) + ray->camera_plane_y * cos(-rotSpeed);
	}
	//data->flag == 99;
	return (ray);
}

void	reraycasting(t_game_data *data)
{
	t_raycast	*ray;
	int			x;

	x = 0;
	ray = recalculate_raycasting_data(data);
	while (x < WIDTH)
	{
		calculate_vars(ray, x);
		calculate_steps(ray);
		wall_hit(data, ray);
		calculate_ray(ray);

		choose_texture(data, ray);
		calculate_line(ray);
		get_pixel_texture(ray);
		draw_line(data, ray, x);
		draw_floor(data, ray, x);
		draw_ceiling(data, ray, x);
		x++;
	}
}
int	rerender(t_game_data *data)
{
	mlx_destroy_image(data->mlx_ptr, data->screen->img_ptr);
	mlx_clear_window(data->mlx_ptr, data->win_ptr);
	data->screen->img_ptr = mlx_new_image(data->mlx_ptr, WIDTH, HEIGHT);
	data->screen->addr = (int *)mlx_get_data_addr(data->screen->img_ptr, &(data->screen->bpp), &(data->screen->len), &(data->screen->ed));
	reraycasting(data);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->screen->img_ptr, 0, 0);
	return (0);
}