/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_sprites2.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: axenth <axenth@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/01 22:34:38 by axenth        #+#    #+#                 */
/*   Updated: 2020/05/07 13:39:07 by jlensing      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	draw_sprites_one(t_data *data, int y, int texx, int texy)
{
	data->img->img_data[(data->img->x * 4 + 4 *
		data->screen_info->screenwidth * y) + 0] =
		mlx_get_color_value(data->mlx_ptr, data->img->sprite_data[(
		texx * 4 + 4 * 64 * texy) + 0]);
	data->img->img_data[(data->img->x * 4 + 4 *
		data->screen_info->screenwidth * y) + 1] =
		mlx_get_color_value(data->mlx_ptr, data->img->sprite_data[(
		texx * 4 + 4 * 64 * texy) + 1]);
	data->img->img_data[(data->img->x * 4 + 4 *
		data->screen_info->screenwidth * y) + 2] =
		mlx_get_color_value(data->mlx_ptr, data->img->sprite_data[(
		texx * 4 + 4 * 64 * texy) + 2]);
}
