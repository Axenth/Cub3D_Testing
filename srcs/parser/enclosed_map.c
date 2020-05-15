/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   enclosed_map.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: jlensing <jlensing@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/08 18:52:16 by jlensing      #+#    #+#                 */
/*   Updated: 2020/05/14 22:21:36 by jlensing      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>
#include <errors.h>
#include <stdlib.h>

static int	**cpy_map(t_data *data, int **tempmap)
{
	int i;
	int j;

	j = 0;
	i = 0;
	tempmap = malloc(sizeof(int*) * data->map_info->mapheight);
	if (tempmap == NULL)
		handle_temp_alloc_fail(data, tempmap, i, 0);
	while (i < data->map_info->mapheight)
	{
		tempmap[i] = malloc(sizeof(int) * data->map_info->mapwidth);
		if (tempmap[i] == NULL)
			handle_temp_alloc_fail(data, tempmap, i, 1);
		while (j < data->map_info->mapwidth)
		{
			tempmap[i][j] = data->map_info->map[i][j];
			j++;
		}
		j = 0;
		i++;
	}
	return (tempmap);
}

static int	**set_edges_loop(t_data *data, int **tempmap, int i)
{
	if (tempmap[i][0] == 0)
		tempmap[i][0] = 2;
	if (tempmap[i][data->map_info->mapwidth - 1] == 0)
		tempmap[i][data->map_info->mapwidth - 1] = 2;
	return (tempmap);
}

static int	**set_edges(t_data *data, int **tempmap)
{
	int i;
	int j;

	i = 1;
	j = 0;
	while (j < data->map_info->mapwidth)
	{
		if (tempmap[0][j] == 0)
			tempmap[0][j] = 2;
		j++;
	}
	j = 0;
	while (i < data->map_info->mapheight - 1)
	{
		tempmap = set_edges_loop(data, tempmap, i);
		i++;
	}
	while (j < data->map_info->mapwidth)
	{
		if (tempmap[data->map_info->mapheight - 1][j] == 0)
			tempmap[data->map_info->mapheight - 1][j] = 2;
		j++;
	}
	return (tempmap);
}

static int	**fill_map(t_data *data, int **tempmap)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (i < data->map_info->mapheight - 1)
	{
		while (j < data->map_info->mapwidth - 1)
		{
			if (tempmap[i][j] == 0)
			{
				tempmap = fill_map_check(data, tempmap, i, j);
				if (tempmap[i][j] == 2)
				{
					i = 0;
					j = 0;
				}
			}
			j++;
		}
		j = 0;
		i++;
	}
	return (tempmap);
}

void		check_map(t_data *data)
{
	int **tempmap;

	tempmap = NULL;
	tempmap = cpy_map(data, tempmap);
	tempmap = set_edges(data, tempmap);
	tempmap = fill_map(data, tempmap);
	if (tempmap[(int)data->player->posx - 1][(int)data->player->posy] == 2)
	{
		data->error = MAP_SURROUND;
	}
	else if (tempmap[(int)data->player->posx + 1][(int)data->player->posy] == 2)
	{
		data->error = MAP_SURROUND;
	}
	else if (tempmap[(int)data->player->posx][(int)data->player->posy + 1] == 2)
	{
		data->error = MAP_SURROUND;
	}
	else if (tempmap[(int)data->player->posx][(int)data->player->posy - 1] == 2)
	{
		data->error = MAP_SURROUND;
	}
	free_tempmap(data, tempmap);
}
