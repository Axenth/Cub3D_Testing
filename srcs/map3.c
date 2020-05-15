/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map3.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: axenth <axenth@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/01 22:51:15 by axenth        #+#    #+#                 */
/*   Updated: 2020/05/15 15:59:20 by jlensing      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>
#include <libft.h>
#include <errors.h>
#include <fcntl.h>

int			get_map_size_2(t_data *data, char *line, int i, int s)
{
	if ((int)ft_strlen(line) > data->map_info->mapwidth)
		data->map_info->mapwidth = (int)ft_strlen(line);
	data->map_info->mapheight++;
	while (line[i] != '\0')
	{
		if (line[i] == '2')
			s++;
		i++;
	}
	return (s);
}

static void	handle_line_3(char *line, t_data *data, int l)
{
	if (ft_strncmp(line, "WE", 2) == 0)
	{
		if (data->parser->we == 0)
			data->img->w_path = ft_substr(line, l, ft_strlen(line) - l);
		data->parser->we += 1;
	}
	else if (ft_strncmp(line, "EA", 2) == 0)
	{
		if (data->parser->ea == 0)
			data->img->e_path = ft_substr(line, l, ft_strlen(line) - l);
		data->parser->ea += 1;
	}
	else if (ft_strncmp(line, "S", 1) == 0)
	{
		if (data->parser->sp == 0)
			data->img->sp_path = ft_substr(line, l, ft_strlen(line) - l);
		data->parser->sp += 1;
	}
}

void		handle_line_2(char *line, t_data *data, int l)
{
	while (*line == ' ')
		line++;
	if (ft_strncmp(line, "NO", 2) == 0)
	{
		if (data->parser->no == 0)
			data->img->n_path = ft_substr(line, l, ft_strlen(line) - l);
		data->parser->no += 1;
	}
	else if (ft_strncmp(line, "SO", 2) == 0)
	{
		if (data->parser->so == 0)
			data->img->s_path = ft_substr(line, l, ft_strlen(line) - l);
		data->parser->so += 1;
	}
	else
	{
		handle_line_3(line, data, l);
	}
}

void		check_path(t_data *data, int flag)
{
	if (flag == 1)
		if (open(data->map_path, O_RDONLY) == -1)
			data->error = MAP_EXIST;
	if (flag == 2)
	{
		if (open(data->img->n_path, O_RDONLY) == -1)
			data->error = TEX_EXIST;
		if (open(data->img->e_path, O_RDONLY) == -1)
			data->error = TEX_EXIST;
		if (open(data->img->s_path, O_RDONLY) == -1)
			data->error = TEX_EXIST;
		if (open(data->img->w_path, O_RDONLY) == -1)
			data->error = TEX_EXIST;
		if (open(data->img->sp_path, O_RDONLY) == -1)
			data->error = TEX_EXIST;
	}
	if (data->error != 0)
		handle_error(data);
}
