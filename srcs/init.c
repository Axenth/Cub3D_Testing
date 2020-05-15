/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jlensing <jlensing@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/13 17:54:34 by jlensing      #+#    #+#                 */
/*   Updated: 2020/05/14 07:30:16 by jlensing      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	init_safety_data(t_data *data)
{
	data->safety.init_failure = 0;
	data->safety.init_ptr = 0;
	data->safety.init_win = 0;
}

void	init_data(t_data *data)
{
	init_parser_info(data);
	data->key_info->key_w = 0;
	data->key_info->key_a = 0;
	data->key_info->key_s = 0;
	data->key_info->key_d = 0;
	data->key_info->key_arrow_left = 0;
	data->key_info->key_arrow_right = 0;
	data->map_info->mapheight = 0;
	data->map_info->mapwidth = 0;
	data->map_info->start_reading = 0;
	data->sprites->amount = 0;
	data->img->textured = 1;
	data->safety.inital_map = 0;
	data->safety.map_flag = 0;
	data->safety.map_count = 0;
	data->safety.sbuffer_flag = 0;
	data->safety.spos_flag = 0;
	data->safety.malloc_sprites = 0;
	read_map(data->map_path, data);
}

void	init_hooks(t_data *data)
{
	mlx_hook(data->mlx_win, 2, 1L << 0, &key_handler, data);
	mlx_hook(data->mlx_win, 3, 1L << 1, &key_release, data);
	mlx_hook(data->mlx_win, 17, 0, exit_game, data);
}
