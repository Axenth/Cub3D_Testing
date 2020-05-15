/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   safety.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jlensing <jlensing@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/09 12:44:03 by jlensing      #+#    #+#                 */
/*   Updated: 2020/05/15 15:43:00 by jlensing      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>
#include <stdlib.h>
#include <errors.h>

static void		free_t_img(t_data *data)
{
	if (data->parser->no >= 1)
		free(data->img->n_path);
	if (data->parser->ea >= 1)
		free(data->img->e_path);
	if (data->parser->so >= 1)
		free(data->img->s_path);
	if (data->parser->we >= 1)
		free(data->img->w_path);
	if (data->parser->sp >= 1)
		free(data->img->sp_path);
	if (data->error != MAP_EXIST)
	{
		if (data->safety.inital_map != 1 && data->safety.sbuffer_flag != 1 &&
			data->safety.spos_flag != 1 && data->parser->resolution != 0)
			free(data->sprites->buffer);
		if (data->safety.malloc_sprites == 1)
		{
			if (data->sprites->x != NULL)
				free(data->sprites->x);
			if (data->sprites->y != NULL)
				free(data->sprites->y);
		}
	}
}

static void		free_other(t_data *data)
{
	int i;

	i = 0;
	if (data->parser->map == 1 && data->error != MAP_ALLOC_FAILURE)
	{
		while (i < data->map_info->mapheight)
		{
			free(data->map_info->map[i]);
			i++;
		}
	}
	else if ((data->error == MAP_ALLOC_FAILURE && data->safety.inital_map == 0)
			|| (data->error == INVALID_MAP_FILE))
	{
		while (i < data->safety.map_count)
		{
			free(data->map_info->map[i]);
			i++;
		}
	}
	if (data->error != MAP_EXIST)
		if (data->safety.inital_map != 1 && data->safety.spos_flag != 1)
			free(data->map_info->map);
}

static void		free_data(t_data *data)
{
	if (data->screen_info != NULL)
		free(data->screen_info);
	if (data->img != NULL)
		free(data->img);
	if (data->camera != NULL)
		free(data->camera);
	if (data->ray != NULL)
		free(data->ray);
	if (data->draw_info != NULL)
		free(data->draw_info);
	if (data->sprite_drawinfo != NULL)
		free(data->sprite_drawinfo);
	if (data->map_info != NULL)
		free(data->map_info);
	if (data->key_info != NULL)
		free(data->key_info);
	if (data->sprites != NULL)
		free(data->sprites);
}

static void		free_all(t_data *data)
{
	if (data->safety.data_flag != 1)
	{
		free_t_img(data);
		free_other(data);
	}
	free_data(data);
}

int				exit_game(t_data *data)
{
	if (data->error != INVALID_ARG)
	{
		free_all(data);
		if (data->error != INVALID_MAP_FILE && data->error != MAP_EXIST &&
			data->error != TEX_EXIST && data->safety.map_flag != 1 &&
			(data->safety.inital_map != 1 || data->safety.init_failure == 1) &&
			data->safety.sbuffer_flag != 1 && data->safety.spos_flag != 1 &&
			data->safety.data_flag != 1)
		{
			if (data->safety.init_win == 0 && data->safety.init_ptr != 1 &&
				data->error != MAP_LOADING)
			{
				mlx_clear_window(data->mlx_ptr, data->mlx_win);
				mlx_destroy_window(data->mlx_ptr, data->mlx_win);
			}
		}
	}
	if (data->parser != NULL)
		free(data->parser);
	free(data);
	system("leaks cub3D");
	exit(1);
	return (0);
}
