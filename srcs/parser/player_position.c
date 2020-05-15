/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   player_position.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: jlensing <jlensing@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/21 01:36:50 by jlensing      #+#    #+#                 */
/*   Updated: 2020/05/15 15:58:39 by jlensing      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

static void	set_north(t_data *data)
{
	data->player->dirx = -1;
	data->player->diry = 0;
	data->player->planex = 0;
	data->player->planey = 0.66;
}

static void	set_east(t_data *data)
{
	data->player->dirx = 0;
	data->player->diry = -1;
	data->player->planex = -0.66;
	data->player->planey = 0;
}

static void	set_south(t_data *data)
{
	data->player->dirx = 1;
	data->player->diry = 0;
	data->player->planex = 0;
	data->player->planey = -0.66;
}

static void	set_west(t_data *data)
{
	data->player->dirx = 0;
	data->player->diry = 1;
	data->player->planex = 0.66;
	data->player->planey = 0;
}

void		set_player_pd(t_data *data, char dir)
{
	data->parser->pl += 1;
	if (dir == 'N')
		set_north(data);
	else if (dir == 'E')
		set_east(data);
	else if (dir == 'S')
		set_south(data);
	else if (dir == 'W')
		set_west(data);
}
