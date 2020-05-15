/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jlensing <jlensing@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/07 02:15:12 by jlensing      #+#    #+#                 */
/*   Updated: 2020/05/14 23:16:07 by jlensing      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <cub3d.h>
#include <errors.h>

static void	load_images(t_data *data, int img_width, int img_height, int bpp)
{
	int size_line;
	int endian;

	size_line = img_width * 4;
	endian = 0;
	data->img->tex1 = mlx_xpm_file_to_image(data->mlx_ptr, data->img->s_path,
													&img_width, &img_height);
	data->img->tex2 = mlx_xpm_file_to_image(data->mlx_ptr, data->img->n_path,
													&img_width, &img_height);
	data->img->tex3 = mlx_xpm_file_to_image(data->mlx_ptr, data->img->e_path,
													&img_width, &img_height);
	data->img->tex4 = mlx_xpm_file_to_image(data->mlx_ptr, data->img->w_path,
													&img_width, &img_height);
	data->img->sprite = mlx_xpm_file_to_image(data->mlx_ptr, data->img->sp_path,
													&img_width, &img_height);
	data->img->tex1_data = mlx_get_data_addr(data->img->tex1, &bpp, &size_line,
																	&endian);
	data->img->tex2_data = mlx_get_data_addr(data->img->tex2, &bpp, &size_line,
																	&endian);
	data->img->tex3_data = mlx_get_data_addr(data->img->tex3, &bpp, &size_line,
																	&endian);
	data->img->tex4_data = mlx_get_data_addr(data->img->tex4, &bpp, &size_line,
																	&endian);
	data->img->sprite_data = mlx_get_data_addr(data->img->sprite, &bpp,
														&size_line, &endian);
}

static void	malloc_data(t_data *data)
{
	data->safety.data_flag = 0;
	data->screen_info = malloc(sizeof(t_screen));
	data->img = malloc(sizeof(t_img));
	data->camera = malloc(sizeof(t_camera));
	data->ray = malloc(sizeof(t_ray));
	data->draw_info = malloc(sizeof(t_drawinfo));
	data->sprite_drawinfo = malloc(sizeof(t_sprite_drawinfo));
	data->map_info = malloc(sizeof(t_map));
	data->key_info = malloc(sizeof(t_keys));
	data->sprites = malloc(sizeof(t_sprites));
	data->parser = malloc(sizeof(t_parser));
	if (data->screen_info == NULL || data->img == NULL ||
		data->camera == NULL || data->ray == NULL || data->draw_info == NULL ||
		data->map_info == NULL || data->sprite_drawinfo == NULL ||
		data->key_info == NULL || data->sprites == NULL || data->parser == NULL)
	{
		data->error = ALLOC_FAILURE;
		data->safety.data_flag = 1;
		handle_error(data);
	}
	init_data(data);
}

static void	init_images(t_data *data)
{
	int bbp;
	int size_line;
	int endian;

	bbp = 32;
	size_line = data->screen_info->screenwidth * 4;
	endian = 0;
	data->img->img = mlx_new_image(data->mlx_ptr,
			data->screen_info->screenwidth, data->screen_info->screenheight);
	data->img->img_data = mlx_get_data_addr(data->img->img, &bbp, &size_line,
																	&endian);
	data->img->img2 = mlx_new_image(data->mlx_ptr,
			data->screen_info->screenwidth, data->screen_info->screenheight);
	data->img->img2_data = mlx_get_data_addr(data->img->img2, &bbp, &size_line,
																	&endian);
	mlx_sync(MLX_SYNC_IMAGE_WRITABLE, data->img->img);
}

int			loop(t_data *data)
{
	int x;

	x = 0;
	move(data);
	rotate(data);
	if (data->error != 0)
		handle_error(data);
	while (x < data->screen_info->screenwidth)
	{
		data->img->x = x;
		init_camera(data);
		x++;
	}
	mlx_put_image_to_window(data->mlx_ptr, data->mlx_win, data->img->img, 0,
																			0);
	if (data->saveopt == 1)
	{
		screenshot("save.bmp", data);
		exit_game(data);
	}
	return (1);
}

int			main(int argv, char **argc)
{
	t_data		*data;
	t_player	player;

	data = malloc(sizeof(t_data));
	if (data == NULL)
		handle_init_error(data, 0);
	check_args(data, argv, argc);
	data->error = 0;
	data->player = &player;
	malloc_data(data);
	data->mlx_ptr = mlx_init();
	init_safety_data(data);
	if (data->mlx_ptr == NULL)
		handle_init_error(data, 1);
	data->mlx_win = mlx_new_window(data->mlx_ptr,
		data->screen_info->screenwidth, data->screen_info->screenheight,
																	"Cub3D");
	if (data->mlx_win == NULL)
		handle_init_error(data, 2);
	check_map(data);
	load_images(data, 64, 64, 32);
	init_images(data);
	init_hooks(data);
	mlx_loop_hook(data->mlx_ptr, loop, data);
	mlx_loop(data->mlx_ptr);
}
