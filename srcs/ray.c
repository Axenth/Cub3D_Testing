/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ray.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: jlensing <jlensing@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/21 12:46:50 by jlensing      #+#    #+#                 */
/*   Updated: 2020/05/07 13:39:07 by jlensing      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	init_ray(t_data *data)
{
	data->ray->mapx = (int)(data->player->posx);
	data->ray->mapy = (int)(data->player->posy);
	data->ray->deltadistx = fabs(1 / data->camera->raydirx);
	data->ray->deltadisty = fabs(1 / data->camera->raydiry);
	data->ray->hit = 0;
	calc_step(data);
}

void	calc_step(t_data *data)
{
	if (data->camera->raydirx < 0)
	{
		data->ray->stepx = -1;
		data->ray->sidedistx = (data->player->posx - data->ray->mapx) *
													data->ray->deltadistx;
	}
	else
	{
		data->ray->stepx = 1;
		data->ray->sidedistx = (data->ray->mapx + 1.0 - data->player->posx) *
														data->ray->deltadistx;
	}
	if (data->camera->raydiry < 0)
	{
		data->ray->stepy = -1;
		data->ray->sidedisty = (data->player->posy - data->ray->mapy) *
														data->ray->deltadisty;
	}
	else
	{
		data->ray->stepy = 1;
		data->ray->sidedisty = (data->ray->mapy + 1.0 - data->player->posy) *
														data->ray->deltadisty;
	}
	calc_dda(data);
}

void	calc_dda(t_data *data)
{
	while (data->ray->hit == 0)
	{
		if (data->ray->sidedistx < data->ray->sidedisty)
		{
			data->ray->sidedistx += data->ray->deltadistx;
			data->ray->mapx += data->ray->stepx;
			data->ray->side = 0;
		}
		else
		{
			data->ray->sidedisty += data->ray->deltadisty;
			data->ray->mapy += data->ray->stepy;
			data->ray->side = 1;
		}
		if (data->map_info->map[data->ray->mapx][data->ray->mapy] > 0)
			data->ray->hit = 1;
	}
	calc_distance(data);
}

void	calc_distance(t_data *data)
{
	if (data->ray->side == 0)
		data->ray->perpwalldist = (data->ray->mapx - data->player->posx +
						(1 - data->ray->stepx) / 2) / data->camera->raydirx;
	else
		data->ray->perpwalldist = (data->ray->mapy - data->player->posy +
						(1 - data->ray->stepy) / 2) / data->camera->raydiry;
	calc_draw(data);
}
