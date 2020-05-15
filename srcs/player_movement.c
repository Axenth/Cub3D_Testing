/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   player_movement.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: jlensing <jlensing@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/07 02:16:02 by jlensing      #+#    #+#                 */
/*   Updated: 2020/05/07 20:04:45 by jlensing      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	move_right(t_data *data)
{
	float lookdirx;
	float lookdiry;

	lookdirx = data->player->diry;
	lookdiry = data->player->dirx;
	if (data->player->diry < 0.0 && data->player->dirx <= 0.0)
	{
		data->player->posy -= lookdiry * MOVESPEED;
		data->player->posx += lookdirx * MOVESPEED;
	}
	else if (data->player->diry < 0.0 && data->player->dirx >= 0.0)
	{
		data->player->posy -= lookdiry * MOVESPEED;
		data->player->posx += lookdirx * MOVESPEED;
	}
	else if (data->player->diry > 0.0 && data->player->dirx >= 0.0)
	{
		data->player->posy -= lookdiry * MOVESPEED;
		data->player->posx += lookdirx * MOVESPEED;
	}
	else if (data->player->diry > 0.0 && data->player->dirx <= 0.0)
	{
		data->player->posy -= lookdiry * MOVESPEED;
		data->player->posx += lookdirx * MOVESPEED;
	}
}

void	move_left(t_data *data)
{
	float lookdirx;
	float lookdiry;

	lookdirx = data->player->diry;
	lookdiry = data->player->dirx;
	if (data->player->diry < 0.0 && data->player->dirx <= 0.0)
	{
		data->player->posy += lookdiry * MOVESPEED;
		data->player->posx -= lookdirx * MOVESPEED;
	}
	else if (data->player->diry < 0.0 && data->player->dirx >= 0.0)
	{
		data->player->posy += lookdiry * MOVESPEED;
		data->player->posx -= lookdirx * MOVESPEED;
	}
	else if (data->player->diry > 0.0 && data->player->dirx >= 0.0)
	{
		data->player->posy += lookdiry * MOVESPEED;
		data->player->posx -= lookdirx * MOVESPEED;
	}
	else if (data->player->diry > 0.0 && data->player->dirx <= 0.0)
	{
		data->player->posy += lookdiry * MOVESPEED;
		data->player->posx -= lookdirx * MOVESPEED;
	}
}
