/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/25 19:41:05 by dromanic          #+#    #+#             */
/*   Updated: 2018/11/14 20:39:16 by dromanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H
# define WIN_WIDTH 1920
# define WIN_HEIGHT 1080
# define WIN_NAME "wolf3d by dromanic (@Dentair)"
# define DEFAULT_MENU_COLOR 0x0f9100FF
# define DEF_FONT "resources/fonts/ARIAL.TTF"
# define DEF_FONT_SIZE 24
# define FRAME_LIMIT 60
# define TEX_WIDTH 64
# define TEX_HEIGHT 64
# define TEXTURES 8
# define DEF_EDGE_TEX 2
# define SHOW_FPS 1
# define DEBUG 0
# define MAX_MAP_SIDE 10000

# include <stdbool.h>
# include <stdlib.h>
# include <math.h>
# include <errno.h>

# include "SDL.h"
# include "SDL_ttf.h"
# include "SDL_image.h"
# include "SDL_mixer.h"
# include "SDL_audio.h"
# include "libft.h"
# include "get_next_line2.h"


/*todo:	red dot aim
	visual editor
	inventory [i]
	pause [p]
	quick belt (fast access)
	menu and splash screen

*/


typedef struct	s_uint32_point
{
	Uint32		x;
	Uint32		y;
}				t_uint32_pt;

typedef struct	s_sint32_point
{
	Sint32		x;
	Sint32		y;
}				t_sint32_pt;

typedef struct	s_double_point
{
	double		x;
	double		y;
}				t_double_pt;

typedef struct	s_sprite
{
	SDL_Surface *image;
	SDL_Rect	rect;
	Uint32		width;
	Uint32		height;
}				t_sprite;

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
	double			current_dist;
	t_double_pt		coords;
	t_double_pt		start;
	t_sint32_pt		texture;
}				t_line;

typedef struct	s_ray
{
	bool			x_less;
	double			wall_x;
	double			x;
	t_double_pt		dist;
	t_double_pt		step;
	t_double_pt		dir;
	t_uint32_pt		pos;
}				t_ray;

typedef struct	s_frame_per_second
{
	u_char		value;
	double		frame_time;
	Uint32		frame_limit_second;
	Uint32		cur_tick;
	Uint32		pre_tick;
}				t_fps;

typedef struct	s_text
{
	int			width;
	int			height;
	char		str[3];
	SDL_Color	color;
	SDL_Surface *sur_str;
	SDL_Texture *tex_str;
	SDL_Rect	rect_txt;
	SDL_Rect	rect_val;
	TTF_Font	*font;
}				t_txt;

typedef struct	s_camera
{
	double			x;
	double			zoom;
	double			move_speed;
	double			min_wall_dist;
	double			rotate_speed;
	t_uint32_pt		center;
	t_sint32_pt		step;
	t_double_pt		pos;
	t_double_pt		dir;
	t_double_pt		plane;
}				t_cam;

typedef struct	s_map
{
	Uint32		**tex_id;
	Uint32		height;
	Uint32		width;
	t_uint32_pt	center;
}				t_map;

typedef struct	s_flags
{
	bool			is_game_over;
	bool			is_move_forward;
	bool			is_move_backward;
	bool			is_strafe_left;
	bool			is_strafe_right;
	bool			is_rotate_left;
	bool			is_rotate_right;
	bool			is_compass_texture;
	unsigned char	mode;
}				t_flags;

typedef struct	s_environment
{
	int				state_arr_length;
	Uint8			bytes_per_pixel;
	Uint8			bits_per_pixel;
	Uint32			err_id;
	Uint32			win_height_x128;
	Sint32			buff[WIN_HEIGHT][WIN_WIDTH];
	Uint32			gen_tex[TEXTURES][TEX_WIDTH * TEX_HEIGHT];
	const Uint8		*state;
	t_flags			flags;
	t_cam			cam;
	t_txt			txt;
	t_fps			fps;
	t_map			map;
	SDL_Surface		**img_tex;
	SDL_Event		event;
	SDL_Window		*window;
	SDL_Renderer	*renderer;
	SDL_Texture		*screen;
	SDL_Surface		*surface;
	Mix_Music		*music;
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
	MAP_SIZE_ERR = 406,
	INVALID_RESOURCE = 407,
	SPACE = 408,
	ITS_A_DIRECTORY = 21
};

t_env			*init_env();
t_env			*parse_map(char *file_name, t_env *env);
void			generate_texture(t_env *env);
void			raycasting(t_env *env, Uint32 **map);
Uint32			chose_color(Uint32 switch_num, bool side);
void			event_handler(t_env *env, t_cam *cam, t_flags *flags);
int				render_interface(t_env *env, t_fps *fps, t_txt *cam);
void			show_errors(t_env *env);
void			quit_program(t_env *env);
#endif
