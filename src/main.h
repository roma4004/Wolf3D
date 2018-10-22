/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/25 19:41:05 by dromanic          #+#    #+#             */
/*   Updated: 2018/10/22 18:53:15 by dromanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H
# define WIN_WIDTH 1920
# define WIN_HEIGHT 1080
# define WIN_NAME "wolf3d by dromanic (@Dentair)"
# define DEFAULT_MENU_COLOR 0x0f9100FF
# define DEF_FONT "fonts/ARIAL.TTF"
# define DEF_FONT_SIZE 24
# define FRAME_LIMIT 60 // todo change this in realtime
//# define mapWidth 24
//# define mapHeight 24
# define TEX_WIDTH 64
# define TEX_HEIGHT 64
# define TEXTURES 8
# define DEBUG 1


//strict max size of map

# include <stdbool.h>
# include <stdlib.h>
# include <math.h>

# include "SDL_ttf.h"
# include "SDL_image.h"
# include "SDL_mixer.h"
# include "SDL_audio.h"
# include "../library/libft/libft.h"
# include "get_next_line.h"
# include <string.h>
# include <errno.h>
# define DEF_EDGE_TEX 2

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
	t_double_pt		coords;
	t_sint32_pt		texture;
	double			current_dist;
	t_double_pt		start;
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
	u_char		value;
	double		frame_time;
	Uint32		frame_limit_second;
	Uint32		current_tick;
	Uint32		previous_tick;
}			t_fps;

typedef struct	s_text
{
	int			width;
	int			height;
	char		str[3];
	SDL_Color	color;
	SDL_Surface *sur_str;
	SDL_Surface *sur_con;
	SDL_Texture *tex_str;
	SDL_Rect	rect_txt;
	SDL_Rect	rect_val;
	TTF_Font	*font;
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
	bool			move_forward;
	bool			move_backward;
	bool			strafe_left;
	bool			strafe_right;
	bool			rotate_left;
	bool			rotate_right;
}				t_cam;

typedef struct	s_map
{
	Uint32		**tex_id;
	Uint32		height;
	Uint32		width;
	Uint32		empty_spaces;
	t_uint32_pt	center;
}				t_map;

typedef struct	s_environment
{
	bool			game_over;
	bool			is_compass_texture;
	unsigned char	mode;
	int				state_arr_length;
	Uint8			bytes_per_pixel;
	Uint8			bits_per_pixel;
	Sint32			img_buff[WIN_HEIGHT][WIN_WIDTH];
	Uint32			gen_tex[TEXTURES][TEX_WIDTH * TEX_HEIGHT];
	const Uint8		*state;
	t_cam			cam;
	t_txt			txt;
	t_fps			fps;
	SDL_Surface		**surfaces;
	SDL_Event		event;
	SDL_Event		my_event;
	SDL_Event		event_mouse;
	SDL_Window		*window;
	SDL_Renderer	*renderer;
	SDL_Texture		*screen;
	SDL_Surface		*surface;
	Mix_Music		*music;
	t_map			map;
	Uint32			error_num;
	Uint32			win_height_x128;
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
	MAP_ERR = 404,
	READ_ERR = 405,
	WIDTH_ERR = 406,
	INVALID_RESOURCE = 407,
	SPACE = 408,
	ITS_A_DIRECTORY = 21
};

t_env			*init_env();
int				render_interface(t_env *env, t_txt *txt);
void			event_handler(t_env *env, t_cam *cam);
Uint32 			chose_color(Uint32 switch_num, bool side);
void			verLine(t_env *env, int x, int start, int end, int color);
void			clear_img_buff(t_env *env);
//int			*init_img_buff(int width, int height);
void			frame_limit(Uint32 current_tick, Uint32 previous_tick,
							Uint32 frame_limit_second);
void			quit_program(t_env *env);
void			raycasting(t_env *env, Uint32 **map);
void			generate_texture(t_env *env);
void			swap_px(t_env *env, Uint32 texSize);
size_t			ft_cnt_words(char *str, size_t max_i, char separator);
t_env			*parse_map(char *file_name, t_env *env);
void			show_errors(t_env *env);
void			move(t_cam *cam, Uint32 **map, double dir_x, double dir_y);
#endif
