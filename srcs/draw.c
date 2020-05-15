/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jlensing <jlensing@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/21 01:41:21 by jlensing      #+#    #+#                 */
/*   Updated: 2020/05/14 23:13:30 by jlensing      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void		calc_draw(t_data *data)
{
	calc_draw_one(data);
	calc_draw_two(data);
	set_sky(data);
}

void		set_sky(t_data *data)
{
	int sky;

	sky = 0;
	while (sky < data->draw_info->drawstart)
	{
		data->img->y = sky;
		set_pixel(data, data->img->ceiling_blue,
					data->img->ceiling_green, data->img->ceiling_red);
		sky++;
	}
	draw_objs(data);
}

void		draw_objs(t_data *data)
{
	while (data->draw_info->drawstart < data->draw_info->drawend)
	{
		data->ray->texy = (int)data->ray->texpos & (TEXHEIGHT - 1);
		data->ray->texpos += data->ray->step;
		data->img->y = data->draw_info->drawstart;
		if (data->img->textured == 1)
		{
			if (data->map_info->map[data->ray->mapx][data->ray->mapy] >= 1)
			{
				if (0 > data->ray->stepx && data->ray->side == 0)
					set_tex_1(data);
				else if (0 <= data->ray->stepx && data->ray->side == 0)
					set_tex_2(data);
				if (data->ray->side == 1)
				{
					if (0 > data->ray->stepy)
						set_tex_3(data);
					else if (0 <= data->ray->stepy)
						set_tex_4(data);
				}
			}
		}
		data->draw_info->drawstart++;
	}
	draw_floor(data);
}

void		draw_floor(t_data *data)
{
	while (data->draw_info->drawstart < data->screen_info->screenheight)
	{
		data->img->y = data->draw_info->drawstart;
		set_pixel(data, data->img->floor_blue,
				data->img->floor_green, data->img->floor_red);
		data->draw_info->drawstart++;
	}
	data->sprites->buffer[data->img->x] = data->ray->perpwalldist;
	draw_sprites(data);
}

void		draw_sprites(t_data *data)
{
	int i;
	int texx;

	i = 0;
	while (i < data->sprites->amount)
	{
		calc_sprite_info(data, i);
		if (data->img->x >= data->sprite_drawinfo->drawstartx &&
			data->img->x <= data->sprite_drawinfo->drawendx)
		{
			texx = (int)(256 * (data->img->x -
				(-data->sprite_drawinfo->spritewidth / 2 +
				data->sprite_drawinfo->spritescreenx)) * 64 /
				data->sprite_drawinfo->spritewidth) / 256;
			draw_sprites_loop(data, texx);
		}
		i++;
	}
}
