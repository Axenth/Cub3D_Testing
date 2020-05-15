/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jlensing <jlensing@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/22 13:51:21 by jlensing      #+#    #+#                 */
/*   Updated: 2020/05/15 15:51:03 by jlensing      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <time.h>
# include <math.h>
# include <mlx.h>
# define ROTSPEED 0.08
# define MOVESPEED 0.08
# define TEXWIDTH 64
# define TEXHEIGHT 64

typedef struct			s_screen
{
	int					screenheight;
	int					screenwidth;
}						t_screen;

typedef struct			s_parser
{
	int					resolution;
	int					no;
	int					so;
	int					we;
	int					ea;
	int					sp;
	int					fl;
	int					ce;
	int					map;
	int					pl;
}						t_parser;

typedef struct			s_player
{
	float				posx;
	float				posy;
	float				dirx;
	float				diry;
	float				planex;
	float				planey;
}						t_player;

typedef struct			s_keys
{
	int					key_w;
	int					key_a;
	int					key_s;
	int					key_d;
	int					key_arrow_left;
	int					key_arrow_right;
}						t_keys;

typedef struct			s_img
{
	void				*img;
	void				*img2;
	char				*n_path;
	char				*e_path;
	char				*s_path;
	char				*w_path;
	char				*sp_path;
	void				*tex1;
	void				*tex2;
	void				*tex3;
	void				*tex4;
	void				*sprite;
	char				*img_data;
	char				*img2_data;
	char				*tex1_data;
	char				*tex2_data;
	char				*tex3_data;
	char				*tex4_data;
	char				*sprite_data;
	int					x;
	int					y;
	int					textured;
	int					floor_red;
	int					floor_green;
	int					floor_blue;
	int					ceiling_red;
	int					ceiling_green;
	int					ceiling_blue;
}						t_img;

typedef struct			s_sprites
{
	int					amount;
	float				*buffer;
	float				*x;
	float				*y;
}						t_sprites;

typedef struct			s_camera
{
	float				camerax;
	float				raydirx;
	float				raydiry;
}						t_camera;

typedef struct			s_ray
{
	int					mapx;
	int					mapy;
	float				sidedistx;
	float				sidedisty;
	float				deltadistx;
	float				deltadisty;
	float				perpwalldist;
	int					stepx;
	int					stepy;
	int					hit;
	int					side;
	float				wallx;
	int					texx;
	int					texy;
	float				step;
	float				texpos;
}						t_ray;

typedef struct			s_sprite_drawinfo
{
	float				spritex;
	float				spritey;
	float				invdet;
	float				transformx;
	float				transformy;
	int					spritescreenx;
	int					spriteheight;
	int					drawstarty;
	int					drawendy;
	int					spritewidth;
	int					drawstartx;
	int					drawendx;
}						t_sprite_drawinfo;

typedef struct			s_drawinfo
{
	int					lineheight;
	int					drawstart;
	int					drawend;
}						t_drawinfo;

typedef struct			s_mapinfo
{
	int					**map;
	int					mapwidth;
	int					mapheight;
	int					start_reading;
}						t_map;

typedef struct			s_saftey
{
	int					map_count;
	int					inital_map;
	int					map_flag;
	int					sbuffer_flag;
	int					spos_flag;
	int					data_flag;
	int					init_failure;
	int					init_ptr;
	int					init_win;
	int					malloc_sprites;
}						t_safety;

typedef struct			s_data
{
	t_screen			*screen_info;
	void				*mlx_ptr;
	void				*mlx_win;
	t_player			*player;
	t_img				*img;
	t_camera			*camera;
	t_ray				*ray;
	t_drawinfo			*draw_info;
	t_sprite_drawinfo	*sprite_drawinfo;
	t_map				*map_info;
	int					error;
	t_keys				*key_info;
	t_sprites			*sprites;
	int					saveopt;
	char				*map_path;
	t_parser			*parser;
	t_safety			safety;
}						t_data;

void					init_data(t_data *data);
void					init_safety_data(t_data *data);
void					init_hooks(t_data *data);
int						key_release(int keycode, t_data *data);
int						key_handler(int keycode, t_data *data);
int						move(t_data *data);
int						rotate(t_data *data);
void					set_pixel(t_data *data, unsigned int red,
									unsigned int green, unsigned int blue);
void					init_ray(t_data *data);
void					init_camera(t_data *data);
void					calc_step(t_data *data);
void					calc_dda(t_data *data);
void					calc_distance(t_data *data);
void					calc_draw(t_data *data);
void					set_sky(t_data *data);
void					draw_objs(t_data *data);
void					draw_floor(t_data *data);
void					read_map(char *path, t_data *data);
void					move_right(t_data *data);
void					move_left(t_data *data);
void					handle_error(t_data *data);
void					set_resolution(char *line, t_data *data);
void					set_floor_color(char *line, t_data *data);
void					set_ceiling_color(char *line, t_data *data);
void					set_player_pd(t_data *data, char dir);
void					draw_sprites(t_data *data);
void					screenshot(char *path, t_data *data);
void					check_map(t_data *data);
int						exit_game(t_data *data);
void					load_map_data(char *line, t_data *data);
int						is_map_line(char *line, t_data *data, int flag);
int						**fill_map_check(t_data *data, int **tempmap,
											int i, int j);
void					malloc_sprites(t_data *data, int amount);
void					calc_sprite_info(t_data *data, int i);
void					free_tempmap(t_data *data, int **tempmap);
void					calc_draw_one(t_data *data);
void					calc_draw_two(t_data *data);
void					set_tex_1(t_data *data);
void					set_tex_2(t_data *data);
void					set_tex_3(t_data *data);
void					set_tex_4(t_data *data);
void					draw_sprites_loop(t_data *data, int texx);
void					draw_sprites_one(t_data *data, int y,
											int texx, int texy);
void					turn_left(t_data *data, float olddirx, float oldplanex);
void					turn_right(t_data *data, float olddirx,
									float oldplanex);
int						get_map_size_2(t_data *data, char *line, int i, int s);
void					calc_fps(t_data *data);
void					check_args(t_data *data, int argv, char **argc);
void					init_parser_info(t_data *data);
int						check_file(t_data *data);
int						check_for_map(t_data *data);
void					handle_line_2(char *line, t_data *data, int l);
int						check_line_cmp(char *line);
void					check_path(t_data *data, int flag);
void					handle_temp_alloc_fail(t_data *data, int **tempmap,
												int i, int flag);
void					handle_gnl_error(t_data *data, int flag);
void					handle_map_error(t_data *data, int flag);
void					handle_bmp_alloc_failure(t_data *data,
												unsigned char *header);
void					handle_init_error(t_data *data, int flag);
void					bmp_info_header_zeroes(unsigned char *bmpinfoheader);

#endif
