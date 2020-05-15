/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   bitmap_header.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: jlensing <jlensing@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/08 15:31:57 by jlensing      #+#    #+#                 */
/*   Updated: 2020/05/14 23:11:50 by jlensing      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <cub3d.h>
#include <errors.h>
#include <fcntl.h>
#include <stdlib.h>

static unsigned char		*init_file_header(t_data *data, int filesize)
{
	unsigned char *bmpfileheader;

	bmpfileheader = malloc(sizeof(char) * 14);
	if (bmpfileheader == NULL)
	{
		data->error = ALLOC_FAILURE;
		handle_error(data);
	}
	bmpfileheader[0] = 'B';
	bmpfileheader[1] = 'M';
	bmpfileheader[2] = (unsigned char)(filesize);
	bmpfileheader[3] = (unsigned char)(filesize >> 8);
	bmpfileheader[4] = (unsigned char)(filesize >> 16);
	bmpfileheader[5] = (unsigned char)(filesize >> 24);
	bmpfileheader[6] = 0;
	bmpfileheader[7] = 0;
	bmpfileheader[8] = 0;
	bmpfileheader[9] = 0;
	bmpfileheader[10] = 54;
	bmpfileheader[11] = 0;
	bmpfileheader[12] = 0;
	bmpfileheader[13] = 0;
	return (bmpfileheader);
}

static unsigned char		*init_info_header(t_data *data,
												int i, unsigned char *header)
{
	unsigned char *bmpinfoheader;

	bmpinfoheader = malloc(sizeof(char) * 40);
	if (bmpinfoheader == NULL)
		handle_bmp_alloc_failure(data, header);
	bmp_info_header_zeroes(bmpinfoheader);
	bmpinfoheader[0] = 40;
	bmpinfoheader[4] = (unsigned char)(data->screen_info->screenwidth);
	bmpinfoheader[5] = (unsigned char)(data->screen_info->screenwidth >> 8);
	bmpinfoheader[6] = (unsigned char)(data->screen_info->screenwidth >> 16);
	bmpinfoheader[7] = (unsigned char)(data->screen_info->screenwidth >> 24);
	bmpinfoheader[8] = (unsigned char)(data->screen_info->screenheight);
	bmpinfoheader[9] = (unsigned char)(data->screen_info->screenheight >> 8);
	bmpinfoheader[10] = (unsigned char)(data->screen_info->screenheight >> 16);
	bmpinfoheader[11] = (unsigned char)(data->screen_info->screenheight >> 24);
	bmpinfoheader[12] = 1;
	bmpinfoheader[14] = 24;
	while (i < 40)
	{
		bmpinfoheader[i] = 0;
		i++;
	}
	return (bmpinfoheader);
}

static void					write_rgb(int fd, t_data *data, int x, int y)
{
	write(fd, &data->img->img_data[(x * (data->screen_info->screenwidth * 4)
													+ y * (32 / 8)) + 0], 1);
	write(fd, &data->img->img_data[(x * (data->screen_info->screenwidth * 4)
													+ y * (32 / 8)) + 1], 1);
	write(fd, &data->img->img_data[(x * (data->screen_info->screenwidth * 4)
													+ y * (32 / 8)) + 2], 1);
}

static void					save_bitmap(int fd, t_data *data)
{
	int				filesize;
	unsigned char	*bmpfileheader;
	unsigned char	*bmpinfoheader;
	int				x;
	int				y;

	filesize = 54 + 3 * data->screen_info->screenwidth *
										data->screen_info->screenheight;
	bmpfileheader = init_file_header(data, filesize);
	bmpinfoheader = init_info_header(data, 16, bmpfileheader);
	write(fd, bmpfileheader, 14);
	write(fd, bmpinfoheader, 40);
	x = data->screen_info->screenheight;
	while (x > 0)
	{
		y = 0;
		while (y < data->screen_info->screenwidth)
		{
			write_rgb(fd, data, x, y);
			y++;
		}
		x--;
	}
	free(bmpfileheader);
	free(bmpinfoheader);
}

void						screenshot(char *path, t_data *data)
{
	int fd;

	fd = open(path, O_RDWR | O_APPEND | O_CREAT | O_TRUNC, 0666);
	if (fd < 0)
	{
		data->error = 79;
		return ;
	}
	save_bitmap(fd, data);
	close(fd);
}
