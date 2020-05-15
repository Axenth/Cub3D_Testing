/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   floor_ceiling_color.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: jlensing <jlensing@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/21 01:31:15 by jlensing      #+#    #+#                 */
/*   Updated: 2020/05/15 15:36:30 by jlensing      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>
#include <libft.h>
#include <errors.h>

static int	check_amount(char *line, t_data *data)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while (line[i] != '\0')
	{
		if (line[i] == ',')
			count++;
		i++;
	}
	if (count != 2)
	{
		data->error = INVALID_MAP_FILE;
		handle_error(data);
	}
	return (1);
}

static void	is_temp_null(char *temp, t_data *data)
{
	if (temp == NULL)
	{
		data->error = MAP_LOADING;
		handle_error(data);
	}
}

static void	too_large(char *temp, t_data *data)
{
	size_t	i;
	int		count;
	int		flag[2];

	flag[0] = 0;
	i = 0;
	count = 0;
	flag[1] = 0;
	while (i < ft_strlen(temp))
	{
		if (temp[i] == ',')
			break ;
		else if (temp[i] >= '0' && temp[i] <= '9' && flag[0] == 0)
			count++;
		else if (temp[i] == ' ' && count >= 1)
			flag[0] = 1;
		else if (temp[i] >= '0' && temp[i] <= '9' && flag[0] == 1)
			flag[1] = 1;
		i++;
	}
	if (flag[1] == 1)
	{
		data->error = INVALID_MAP_FILE;
		handle_error(data);
	}
}

void		set_floor_color(char *line, t_data *data)
{
	char *temp;

	while (*line == ' ')
		line++;
	check_amount(line, data);
	temp = ft_strchr(line, ' ');
	is_temp_null(temp, data);
	too_large(temp, data);
	data->img->floor_red = ft_atoi(temp);
	temp = ft_strchr(temp, ',');
	is_temp_null(temp, data);
	temp++;
	too_large(temp, data);
	data->img->floor_green = ft_atoi(temp);
	temp = ft_strrchr(temp, ',');
	is_temp_null(temp, data);
	temp++;
	too_large(temp, data);
	data->img->floor_blue = ft_atoi(temp);
	temp = NULL;
	data->parser->fl += 1;
	if (data->img->floor_blue > 255 || data->img->floor_red > 255 ||
		data->img->floor_green > 255)
		data->error = INVALID_MAP_FILE;
}

void		set_ceiling_color(char *line, t_data *data)
{
	char *temp;

	while (*line == ' ')
		line++;
	check_amount(line, data);
	temp = ft_strchr(line, ' ');
	is_temp_null(temp, data);
	too_large(temp, data);
	data->img->ceiling_red = ft_atoi(temp);
	temp = ft_strchr(temp, ',');
	is_temp_null(temp, data);
	temp++;
	too_large(temp, data);
	data->img->ceiling_green = ft_atoi(temp);
	temp = ft_strrchr(temp, ',');
	is_temp_null(temp, data);
	temp++;
	too_large(temp, data);
	data->img->ceiling_blue = ft_atoi(temp);
	temp = NULL;
	data->parser->ce += 1;
	if (data->img->ceiling_red > 255 || data->img->ceiling_green > 255 ||
		data->img->ceiling_blue > 255)
		data->error = INVALID_MAP_FILE;
}
