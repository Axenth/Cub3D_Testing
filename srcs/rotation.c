/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   rotation.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: axenth <axenth@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/01 22:44:10 by axenth        #+#    #+#                 */
/*   Updated: 2020/05/07 20:04:29 by jlensing      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	turn_right(t_data *data, float olddirx, float oldplanex)
{
	data->player->dirx = data->player->dirx * cos(-ROTSPEED) -
								data->player->diry * sin(-ROTSPEED);
	data->player->diry = olddirx * sin(-ROTSPEED) +
								data->player->diry * cos(-ROTSPEED);
	data->player->planex = data->player->planex * cos(-ROTSPEED) -
								data->player->planey * sin(-ROTSPEED);
	data->player->planey = oldplanex * sin(-ROTSPEED) +
								data->player->planey * cos(-ROTSPEED);
}

void	turn_left(t_data *data, float olddirx, float oldplanex)
{
	data->player->dirx = data->player->dirx * cos(ROTSPEED) -
								data->player->diry * sin(ROTSPEED);
	data->player->diry = olddirx * sin(ROTSPEED) +
								data->player->diry * cos(ROTSPEED);
	data->player->planex = data->player->planex * cos(ROTSPEED) -
								data->player->planey * sin(ROTSPEED);
	data->player->planey = oldplanex * sin(ROTSPEED) +
								data->player->planey * cos(ROTSPEED);
}
