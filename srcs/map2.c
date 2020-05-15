/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map2.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jlensing <jlensing@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/19 16:27:30 by jlensing      #+#    #+#                 */
/*   Updated: 2020/05/14 07:47:50 by jlensing      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>
#include <libft.h>
#include <stdlib.h>
#include <errors.h>

static void	load_map_data_loop2(char *line, t_data *data, int count, int j)
{
	if (line[j] == '1' || line[j] == '0' || line[j] == ' ')
	{
		if (line[j] == '1' || line[j] == '0')
			data->map_info->map[count][j] = line[j] - '0';
	}
	else if (line[j] == ' ')
		data->map_info->map[count][j] = 0;
}

static int	load_map_data_loop(char *line, t_data *data, int count, int j)
{
	static int	scount = 0;

	while (j < (int)ft_strlen(line))
	{
		if (line[j] == 'N' || line[j] == 'E' || line[j] == 'S' ||
														line[j] == 'W')
		{
			data->map_info->map[count][j] = 0;
			data->player->posx = count;
			data->player->posy = j;
			set_player_pd(data, line[j]);
		}
		else if (line[j] == '2')
		{
			data->map_info->map[count][j] = 0;
			data->sprites->x[scount] = count + 0.5;
			data->sprites->y[scount] = j + 0.5;
			scount++;
		}
		else
			load_map_data_loop2(line, data, count, j);
		j++;
	}
	return (j);
}

void		load_map_data(char *line, t_data *data)
{
	static int	count = 0;
	int			j;

	j = 0;
	data->map_info->map[count] = malloc(sizeof(int) * data->map_info->mapwidth);
	if (data->map_info->map[count] == NULL)
	{
		data->safety.map_count = count;
		data->safety.map_flag = 1;
		data->error = MAP_ALLOC_FAILURE;
		handle_error(data);
	}
	j = load_map_data_loop(line, data, count, 0);
	while (j >= (int)ft_strlen(line) && j < data->map_info->mapwidth)
	{
		data->map_info->map[count][j] = 0;
		j++;
	}
	count++;
	data->safety.map_count = count;
}

int			is_map_line(char *line, t_data *data, int flag)
{
	int		never;
	int		ismap;
	int		i;

	i = 0;
	ismap = 0;
	never = 0;
	while (line[i] != '\0')
	{
		if ((line[i] == '0' || line[i] == '1') &&
										i < (int)ft_strlen(line) - 1)
			if (line[i + 1] == '0' || line[i + 1] == '1' || line[i + 1] == ' ')
				ismap = 1;
		if ((ft_isalpha(line[i]) && line[i] != ' ') ||
											(line[i] >= '3' && line[i] <= '9'))
			if (line[i] != 'N' && line[i] != 'E' &&
										line[i] != 'S' && line[i] != 'W')
				never = 1;
		i++;
	}
	if (never)
		ismap = 0;
	if (ismap == 1 && flag == 1)
		data->map_info->start_reading = 1;
	return (ismap);
}

void		malloc_sprites(t_data *data, int amount)
{
	data->sprites->amount = amount;
	data->sprites->x = malloc(sizeof(float) * data->sprites->amount);
	data->sprites->y = malloc(sizeof(float) * data->sprites->amount);
	if (data->sprites->x == NULL || data->sprites->y == NULL)
	{
		data->error = ALLOC_FAILURE;
		data->safety.spos_flag = 1;
		handle_error(data);
	}
	data->safety.malloc_sprites = 1;
}
