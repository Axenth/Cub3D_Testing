/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   resolution.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jlensing <jlensing@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/21 01:36:40 by jlensing      #+#    #+#                 */
/*   Updated: 2020/05/15 16:01:42 by jlensing      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>
#include <errors.h>
#include <libft.h>
#include <stdlib.h>

static void	set_resolution2(char *line, t_data *data)
{
	char	*temp;
	int		x;
	int		y;

	while (*line == ' ')
		line++;
	temp = ft_strchr(line, ' ');
	data->screen_info->screenwidth = ft_atoi(temp);
	temp = ft_strrchr(line, ' ');
	data->screen_info->screenheight = ft_atoi(temp);
	temp = NULL;
	mlx_get_screen_size(data->mlx_ptr, &x, &y);
	if (data->screen_info->screenwidth > x)
		data->screen_info->screenwidth = x;
	if (data->screen_info->screenheight > y)
		data->screen_info->screenheight = y;
	data->sprites->buffer = malloc(sizeof(float)
							* data->screen_info->screenwidth);
	if (data->sprites->buffer == NULL)
	{
		data->safety.sbuffer_flag = 1;
		data->error = ALLOC_FAILURE;
		handle_error(data);
	}
}

void	set_resolution(char *line, t_data *data)
{
	if (data->parser->resolution == 0)
		set_resolution2(line, data);
	data->parser->resolution += 1;
}
