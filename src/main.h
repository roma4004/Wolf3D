/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/25 19:41:05 by dromanic          #+#    #+#             */
/*   Updated: 2018/10/18 17:50:20 by dromanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H
# define WIN_WIDTH 1800
# define WIN_HEIGHT 1200
# define WIN_NAME "wolf3d by dromanic (@Dentair)"
# define DEFAULT_MENU_COLOR 0x0f9100FF
# define DEF_FONT "fonts/ARIAL.TTF"
# define DEF_FONT_SIZE 24
# define FRAME_LIMIT 60 // todo change this in realtime
# define mapWidth 24
# define mapHeight 24
# define tex_width 64
# define tex_height 64
# define texture_count 9
# define WIDTH_ERR_SKIP 0

# include <stdbool.h>
# include <stdlib.h>
# include <math.h>

# include "SDL_ttf.h"
# include "SDL_image.h"
# include "SDL_mixer.h"
# include "../library/libft/libft.h"
# include "get_next_line.h"
# include <string.h>
# include <errno.h>

typedef struct	s_uint32_point
{
	Uint32		x;
	Uint32		y;
}			t_uint32_pt;

typedef struct	s_sint32_point
{
	Sint32		x;
	Sint32		y;
}			t_sint32_pt;

typedef struct	s_double_pt
{
	double		x;
	double		y;
}			t_double_pt;

typedef struct	s_sprite
{
	SDL_Surface *image;
	SDL_Rect	rect;
	Uint32		width;
	Uint32		height;
}			t_sprite;

typedef struct	s_line
{
	unsigned int	side;
	Uint32			tex_num;
	Uint32			*img;
	Uint32			x;
	Uint32			tex_y;
	Uint32			start_y;
	Uint32			end_y;
	Uint32			color;
	Uint32			scale;
	double			height;
	double			half;
	double			normal;

	double			weight;
	t_double_pt		currentFloor;
	t_sint32_pt		texture;
	double			current_dist;
	t_double_pt		floor_wall;
}			t_line;

typedef struct	s_ray
{
	bool			x_less;
	double			wall_x;
	double			x;
	t_double_pt		dist;
	t_double_pt		step;
	t_double_pt		dir;
	t_uint32_pt		pos;
}			t_ray;

typedef struct	s_frame_per_second
{
	float		value;
	double		frame_time;
	Uint32		frame_limit_second;
	Uint32		current_tick;
	Uint32		previous_tick;
}			t_fps;

typedef struct	s_text
{
	int			width;
	int			height;
	char		text[3];
	SDL_Color	color;
	SDL_Rect	rect;
	TTF_Font	*messageFont;
}				t_txt;

typedef struct	s_camera
{
	t_sint32_pt		step;
	t_double_pt		pos;
	t_double_pt		dir;
	double			x;
	double			zoom;
	t_double_pt		plane;
	double			move_speed;
	double			min_wall_dist;
	double			rotate_speed;
	t_uint32_pt		center;
	double			wall_scale;
}			t_cam;

typedef struct	s_wall
{
	Uint32	tex_id;

	Uint32	n_side;
	Uint32	w_side;
	Uint32	e_side;
	Uint32	s_side;
}				t_wall;

typedef struct	s_environment
{
	bool			game_over;
	bool			is_compass_texture;
	unsigned char	tex_mode;
	int				state_arr_length;
	Uint8			bytes_per_pixel;
	Uint8			bits_per_pixel;
	Sint32			img_buff[WIN_HEIGHT][WIN_WIDTH];
	Uint32			gen_texture[texture_count][tex_width * tex_height];
	const Uint8		*state;
	t_cam			cam;
	t_txt			txt;
	t_fps			fps;
	SDL_Surface		**surfaces;
	SDL_DisplayMode	display_param;
	SDL_Event		event;
	SDL_Window		*window;
	SDL_Renderer	*renderer;
	SDL_Texture		*screen;
	SDL_Surface		*surface;

	t_wall			**map;
//	Uint32			map_height;
//	Uint32			map_width;
	Uint32			map_center_y;
	Uint32			map_center_x;
	Uint32			error_code;
}				t_env;

enum			e_colors
{
	RED = 0xFF0000,
	GREEN = 0x00FF00,
	BLUE = 0x0000FF,
	WHITE = 0xFFFFFF,
	YELLOW = 0xFFFF00
};

enum			e_errors
{
	MAP_INVALID = 404,
	WIDTH_ERR = 405,
	READ_ERR = 406,
	COLOR_ERR = 407,
	ITS_A_DIRECTORY = 21
};

t_env			*init_env();
//int				display_interface();
void			event_handler(t_env *env, Uint32 [mapWidth][mapHeight]);
Uint32 			chose_color(Uint32 switch_num, bool side);
void			verLine(t_env *env, int x, int start, int end, int color);
void			clear_img_buff(t_env *env);
//int			*init_img_buff(int width, int height);
void			frame_limit(Uint32 current_tick, Uint32 previous_tick,
							Uint32 frame_limit_second);
void			quit_program(t_env *env);
void			raycasting(t_env *env,
								Uint32 worldMap[mapWidth][mapHeight]);
Uint32			*chose_gen_or_image(t_env *env, Uint32 gen_id, Uint32 img_id);
void			generate_texture(t_env *env);
void			swap_px(t_env *env, Uint32 texSize);
#endif
