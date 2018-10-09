/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/25 19:41:05 by dromanic          #+#    #+#             */
/*   Updated: 2018/10/09 18:31:20 by dromanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H
# define WIN_WIDTH 1024
# define WIN_HEIGHT 768
# define WIN_NAME "wolf3d by dromanic (@Dentair)"
# define DEFAULT_MENU_COLOR 0x0f9100FF
# define DEF_FONT "fonts/ARIAL.TTF"
#define FRAME_LIMIT 80
#define mapWidth 24
#define mapHeight 24

#include <stdbool.h>

# include <stdlib.h>
# include <stdio.h>
# include <math.h>
# include <string.h>

//# include "../library/frameworks/SDL2.framework/Headers/extern.h"
//# include <SDL2/SDL.h>
//#include "../library/frameworks/SDL2_ttf.framework/Versions/A/Headers/SDL_ttf.h"
//#include "../library/frameworks/SDL2_image.framework/Versions/A/Headers/SDL_image.h"
//# include <SDL2/SDL.h>
//# include <SDL2_ttf/SDL_ttf.h>
# include "../library/frameworks/SDL2_ttf.framework/Headers/SDL_ttf.h"
# include "../library/frameworks/SDL2_image.framework/Headers/SDL_image.h"
# include "../library/frameworks/SDL2_mixer.framework/Headers/SDL_mixer.h"
# include "../library/libft/libft.h"

typedef struct	s_environment
{
	SDL_Window		*window;
	SDL_Renderer	*renderer;
	SDL_Texture		*mainTexture;
	SDL_Surface		*surface;
	Sint32			img_buff[WIN_HEIGHT][WIN_WIDTH];

	Uint32			framesTimesindex;
	Uint32			getticks;
	float			fps;
	Uint32			framesTimes[FRAME_LIMIT];
	Uint32			frameTimeLast;
	Uint32			frameCount;
	SDL_Texture		*texture;
	SDL_DisplayMode	display_param;
	SDL_Event		event;
	bool			game_over;
	double			moveSpeed;
	double			rotateSpeed;
	double			frameTime;

	double			posX;
	double			posY;
	double			dirX;
	double			dirY;
	Sint32			stepX;
	Sint32 			stepY;
	Sint32			mapX;
	Sint32			mapY;
	Sint32			side;//was a NS or a EW wall hit?
	Sint32			hit;
	double			planeX;
	double			planeY;
	double			rayDirX;
	double			rayDirY;
	double			cameraX;
	double			sideDistX;
	double			sideDistY;
	double			deltaDistX;
	double			deltaDistY;
	double			perpWallDist;

	Uint32			current_tick;
	Uint32			previous_tick;
//vector			texture[8];
	const Uint8		*state;
	int				state_arr_length;
}				t_env;

typedef struct	s_sprite
{
	SDL_Surface *image;
	SDL_Rect	rect;
	Uint32		width;
	Uint32		height;
}				t_sprite;


typedef struct	s_text
{
	int			messageWidth;
	int			messageHeight;
	SDL_Color	messageColor;
	SDL_Rect	rect;
}				t_txt;

enum			e_colors
{
	RED = 0xFF0000,
	GREEN = 0x00FF00,
	BLUE = 0x0000FF,
	WHITE = 0xFFFFFF,
	YELLOW = 0xFFFF00
};

enum			e_keys_code
{
	NUM_1 = 83, ONE = 18,
	NUM_2 = 84, TWO = 19,
	NUM_3 = 85, THREE = 20,
	NUM_4 = 86, FOUR = 21,
	NUM_5 = 87, FIVE = 23,
	NUM_6 = 88, SIX = 22,
	NUM_7 = 89, SEVEN = 26,
	NUM_8 = 91, EIGHT = 28, MINUS = 27,
	NUM_9 = 92, NINE = 25, PLUS = 24,
	NUM_0 = 82, ZERO = 29, NUM_MINUS = 78,
	NUM_DIV = 75, NUM_MUL = 67, NUM_PLUS = 69,
	MOUSE_SCROLL_UP = 4, MOUSE_LBT = 1,
	MOUSE_SCROLL_DOWN = 5, MOUSE_RBT = 2,
	Q = 12, W = 13, E = 14, R = 15, T = 17, Y = 16, U = 32,
	A = 0, S = 1, D = 2, F = 3, G = 5, H = 4, J = 38,
	Z = 6, X = 7, C = 8, V = 9, B = 11, N = 45, M = 46,
	ENTER = 36, ESC = 53,
	ARROW_UP = 126, ARROW_DOWN = 125,
	ARROW_LEFT = 123, ARROW_RIGHT = 124,
	HOME = 115, PAGE_UP = 116,
	END = 119, PAGE_DOWN = 121
};

//wolf3d
t_env			*init_env();
int				display_interface(t_env *env);
void			event_handler(t_env *env, Sint32 [mapWidth][mapHeight]);
Sint32 			chose_color(Sint32 switch_num, Sint32 side);
void			verLine(t_env *env, int x, int start, int end, int color);
void			clear_img_buff(t_env *env);
//int			*init_img_buff(int width, int height);
void			frame_limit(Uint32 current_tick, Uint32 previous_tick);
#endif
