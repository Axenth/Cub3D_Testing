/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: jlensing <jlensing@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/22 15:57:06 by jlensing      #+#    #+#                 */
/*   Updated: 2020/05/15 15:58:26 by jlensing      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <cub3d.h>
#include <errors.h>
#include <libft.h>

static int		find_start(char *line)
{
	int i;

	while(*line == ' ')
		line++;
	i = 2;
	if (ft_strlen(line) == 0)
		return (0);
	if (line[i - 2] == 'S' && line[i - 1] == ' ')
		i = 1;
	while (line[i] != '\0')
	{
		if (line[i] != ' ')
			return (i);
		i++;
	}
	return (0);
}

static void		handle_line(char *line, t_data *data)
{
	int l;

	l = find_start(line);
	if (check_line_cmp(line) == 2)
		set_resolution(line, data);
	else if (check_line_cmp(line) == 1)
		handle_line_2(line, data, l);
	else if (check_line_cmp(line) == 3)
		set_floor_color(line, data);
	else if (check_line_cmp(line) == 4)
		set_ceiling_color(line, data);
	else if (ft_strlen(line) == 0 && data->map_info->start_reading == 1)
	{
		data->error = INVALID_MAP_FILE;
		handle_error(data);
	}
	else if (ft_strlen(line) == 0)
		return ;
	else if (is_map_line(line, data, 1) && check_for_map(data) == 1)
		load_map_data(line, data);
	else
	{
		data->error = INVALID_MAP_FILE;
		handle_error(data);
	}
}

static void		get_map_size(char *path, t_data *data)
{
	int		fd;
	int		ret;
	char	*line;
	int		i;
	int		s;

	i = 0;
	s = 0;
	ret = 1;
	data->parser->pl = 0;
	fd = open(path, O_RDONLY);
	while (ret > 0)
	{
		ret = get_next_line(fd, &line);
		if (ret == -1)
			handle_gnl_error(data, 0);
		if (is_map_line(line, data, 0))
		{
			s = get_map_size_2(data, line, i, s);
		}
		i = 0;
		free(line);
	}
	malloc_sprites(data, s);
	line = NULL;
}

void			read_map(char *path, t_data *data)
{
	int		fd;
	int		ret;
	char	*line;

	check_path(data, 1);
	line = "";
	ret = 1;
	get_map_size(path, data);
	fd = open(path, O_RDONLY);
	data->map_info->map = malloc(sizeof(int*) * data->map_info->mapheight);
	if (data->map_info->map == NULL)
		handle_map_error(data, 0);
	while (ret > 0)
	{
		ret = get_next_line(fd, &line);
		if (ret == -1)
			handle_gnl_error(data, 1);
		handle_line(line, data);
		free(line);
	}
	data->parser->map = 1;
	check_path(data, 2);
	if (check_for_map(data) == 0 || data->parser->pl != 1)
		handle_map_error(data, 1);
	close(fd);
}
