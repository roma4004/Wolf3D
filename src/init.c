/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/22 17:23:17 by dromanic          #+#    #+#             */
/*   Updated: 2018/10/21 21:07:46 by dromanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

SDL_Surface		*load_surface(t_env *env, char *path_name)
{
	SDL_Surface			*new_srf;
	SDL_Surface			*convert_srf;
	SDL_PixelFormat		px_format;

	if (!env || !path_name)
		return (NULL);
	px_format.format = SDL_PIXELFORMAT_ARGB8888;
	px_format.palette = NULL;
	px_format.BytesPerPixel = sizeof(Uint32);
	px_format.BitsPerPixel = px_format.BytesPerPixel * (Uint8)8;
	px_format.Rmask = 0;
	px_format.Gmask = 0;
	px_format.Bmask = 0;
	px_format.Amask = 0;
	if (!(new_srf = IMG_Load(path_name))
	|| !(convert_srf = SDL_ConvertSurface(new_srf, &px_format, 0)))
	{
		ft_putstr(SDL_GetError());
		ft_putchar('\n');
		env->error_num = INVALID_RESOURCE;
		return (NULL);
	}
	if (new_srf)
		SDL_FreeSurface(new_srf);
	return (convert_srf);
}

//uint32_t		*init_img_buff(uint32_t width, uint32_t height)
//{
//	uint32_t		*new_img_buff;
//
//	if ((new_img_buff = (uint32_t *)malloc(sizeof(uint32_t) * (width * height))))
//	{
//		return (new_img_buff);
//	}
//	return (NULL);
//}
//t_txt		*init_text()
//{
//	t_txt *new_text;
//
//	new_text.font = TTF_OpenFont(DEF_FONT, DEF_FONT_SIZE)
//}

t_env		*env_def_val(t_env *env)
{
	if (!env)
		return (NULL);
	env->game_over = false;
	env->is_compass_texture = 1;
	env->mode = 2; //need to switch this in realtime (and correctly free)
	env->cam.dir.x = -1;
	env->cam.dir.y = 0;
	env->cam.plane.x = 0;//need to change in real time (give psihodelic effect)
	env->cam.plane.y = 0.66; //the 2d raycaster version of camera plane
	env->fps.current_tick = 0; //current_tick of current frame
	env->fps.previous_tick = 0; //current_tick of previous frame
	env->cam.center.x = WIN_WIDTH >> 1;
	env->cam.center.y = WIN_HEIGHT >> 1;
	env->fps.frame_limit_second = 1000 / FRAME_LIMIT;
	env->cam.zoom = 1;
	env->bytes_per_pixel = sizeof(Uint32);
	env->bits_per_pixel = env->bytes_per_pixel * (unsigned char)8;
	env->cam.wall_scale = 1;
	//env->fps.frames = 0;
	env->win_height_x128 = WIN_HEIGHT * 128;
	generate_texture(env);
	SDL_SetRelativeMouseMode(SDL_TRUE);
	env->surfaces[0] = load_surface(env, "textures/eagle.png");
	env->surfaces[1] = load_surface(env, "textures/red_brick.png");
	env->surfaces[2] = load_surface(env, "textures/purple_stone.png");
	env->surfaces[3] = load_surface(env, "textures/grey_stone.png");
	env->surfaces[4] = load_surface(env, "textures/blue_stone.png");
	env->surfaces[5] = load_surface(env, "textures/mossy.png");
	env->surfaces[6] = load_surface(env, "textures/wood.png");
	env->surfaces[7] = load_surface(env, "textures/color_stone.png");
	if (env->error_num)
		return (NULL);
	env->txt.color = (SDL_Color){255, 255, 255, 0};
	env->txt.width = 0;
	env->txt.height = 0;
	env->cam.pos.x = 0;
	env->cam.pos.y = 0;
	env->map.empty_spaces = 0;
	env->cam.min_wall_dist = 2.5;
	return (env);
}

t_env	*init_env(void)
{
	t_env	*new_env;

	if (!(new_env = (t_env *)malloc(sizeof(t_env)))
	||  (new_env->error_num = 0)
	|| (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_EVENTS))
	|| (TTF_Init() == -1)
	|| (!(new_env->window = SDL_CreateWindow(WIN_NAME, //SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
			WIN_WIDTH, WIN_HEIGHT, SDL_WINDOW_RESIZABLE))) //SDL_WINDOW_FULLSCREEN || SDL_WINDOW_RESIZABLE
	|| !(new_env->renderer = SDL_CreateRenderer(new_env->window, -1,
			SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC))
	|| !(new_env->screen = SDL_CreateTexture(new_env->renderer,
			SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_TARGET,
			WIN_WIDTH, WIN_HEIGHT))
	|| (SDL_GetDesktopDisplayMode(0, &new_env->display_param))
	|| !(new_env->state = SDL_GetKeyboardState(&new_env->state_arr_length))
	|| !(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)
	|| !(new_env->surfaces =
			(SDL_Surface **)malloc(sizeof(SDL_Surface *) * TEXTURES))
	|| !(new_env->txt.font = TTF_OpenFont(DEF_FONT, DEF_FONT_SIZE))
	|| (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	|| !(new_env->music = Mix_LoadMUS("sounds/horst_wessel_lied.wav"))
	|| !(env_def_val(new_env)))
	{
		if (!new_env->error_num)
			ft_putstr(SDL_GetError());
		//new_env->error_num = 1;
		//display_errors;
	}
	if (new_env->error_num)
	{
		show_errors(new_env);
		quit_program(new_env);
		return (NULL);
	}
	return (new_env);
}

//		|| !(new_env->img_buff = init_img_buff((uint32_t)WIN_WIDTH, (uint32_t)WIN_HEIGHT))
//		|| !(new_env->screen =
//				SDL_CreateTexture(new_env->renderer, SDL_PIXELFORMAT_ARGB8888,
//						SDL_TEXTUREACCESS_STATIC, WIN_WIDTH, WIN_HEIGHT))
//img_buff is not two dimensional
