/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   enclosed_map_2.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: jlensing <jlensing@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/26 20:01:09 by jlensing      #+#    #+#                 */
/*   Updated: 2020/05/13 17:51:23 by jlensing      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>
#include <stdlib.h>
#include <errors.h>

int		**fill_map_check(t_data *data, int **tempmap, int i, int j)
{
	if (i > 0 && tempmap[i - 1][j] == 2)
		tempmap[i][j] = 2;
	if (i < data->map_info->mapheight - 1 && tempmap[i + 1][j] == 2)
		tempmap[i][j] = 2;
	if (j > 0 && tempmap[i][j - 1] == 2)
		tempmap[i][j] = 2;
	if (j < data->map_info->mapwidth - 1 && tempmap[i][j + 1] == 2)
		tempmap[i][j] = 2;
	return (tempmap);
}

void	free_tempmap(t_data *data, int **tempmap)
{
	int i;

	i = 0;
	while (i < data->map_info->mapheight)
	{
		free(tempmap[i]);
		i++;
	}
	free(tempmap);
}

void	handle_temp_alloc_fail(t_data *data, int **tempmap, int i, int flag)
{
	int x;

	x = 0;
	if (flag == 1)
	{
		while (x < i)
		{
			free(tempmap[x]);
			x++;
		}
		free(tempmap);
	}
	data->error = ALLOC_FAILURE;
	handle_error(data);
}
