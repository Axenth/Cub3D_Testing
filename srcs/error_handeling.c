/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error_handeling.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: jlensing <jlensing@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/28 15:44:44 by jlensing      #+#    #+#                 */
/*   Updated: 2020/05/13 18:11:27 by jlensing      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>
#include <errors.h>
#include <libft.h>
#include <stdlib.h>

void	handle_error(t_data *data)
{
	if (data->error == MAP_SURROUND)
		ft_printf("Error\nMap is not fully enclosed\n");
	if (data->error == INVALID_MAP_FILE)
		ft_printf("Error\nInvalid map configuriation\n");
	if (data->error == FD_FAILED)
		ft_printf("Error\nA File Descriptor failed to initialize\n");
	if (data->error == INVALID_ARG)
		ft_printf("Error\nInvalid Arguments\n");
	if (data->error == MAP_EXIST)
		ft_printf("Error\nMap does not exist\n");
	if (data->error == TEX_EXIST)
		ft_printf("Error\nTexture does not exist\n");
	if (data->error == MAP_LOADING)
		ft_printf("Error\nLoading map failed\n");
	if (data->error == ALLOC_FAILURE)
		ft_printf("Error\nMemory allocation failed\n");
	if (data->error == MAP_ALLOC_FAILURE)
		ft_printf("Error\nMap memory allocation failed\n");
	if (data->error == INIT_FAILURE)
	{
		ft_printf("Error\nMLX initialization failed\n");
		data->safety.init_failure = 1;
	}
	exit_game(data);
}

void	check_args(t_data *data, int argv, char **argc)
{
	if (argv > 1 && argv <= 3)
	{
		data->map_path = argc[1];
		if (argv == 3)
		{
			if (ft_strncmp(argc[2], "--save", 6) == 0)
				data->saveopt = 1;
			else
			{
				data->error = 76;
				handle_error(data);
			}
		}
	}
	else
	{
		data->error = 76;
		handle_error(data);
	}
}

void	handle_gnl_error(t_data *data, int flag)
{
	if (flag == 0)
	{
		data->error = MAP_ALLOC_FAILURE;
		data->safety.inital_map = 1;
		handle_error(data);
	}
	else
	{
		data->error = MAP_LOADING;
		data->safety.sbuffer_flag = 1;
		handle_error(data);
	}
}

void	handle_map_error(t_data *data, int flag)
{
	if (flag == 0)
	{
		data->safety.inital_map = 1;
		data->error = MAP_ALLOC_FAILURE;
		handle_error(data);
	}
	else
	{
		data->error = INVALID_MAP_FILE;
		handle_error(data);
	}
}

void	handle_init_error(t_data *data, int flag)
{
	if (flag == 0)
	{
		ft_printf("Error\nMemory allocation failure\n");
		exit(1);
	}
	data->error = INIT_FAILURE;
	if (flag == 1)
		data->safety.init_ptr = 1;
	else if (flag == 2)
		data->safety.init_win = 1;
	handle_error(data);
}
