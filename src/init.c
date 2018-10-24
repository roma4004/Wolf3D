/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/22 17:23:17 by dromanic          #+#    #+#             */
/*   Updated: 2018/10/24 17:31:44 by dromanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

SDL_Surface			*load_surface(t_env *env, char *path_name)
{
	SDL_Surface			*new_srf;
	SDL_Surface			*convert_srf;
	SDL_PixelFormat		px_format;

	if (!env || !path_name)
		return (NULL);
	px_format.format = SDL_PIXELFORMAT_ARGB8888;
	px_format.palette = NULL;
	px_format.BytesPerPixel = sizeof(Uint32);
	px_format.BitsPerPixel = (Uint8)(px_format.BytesPerPixel * 8);
	px_format.Rmask = 0;
	px_format.Gmask = 0;
	px_format.Bmask = 0;
	px_format.Amask = 0;
	if (!(new_srf = IMG_Load(path_name))
	|| !(convert_srf = SDL_ConvertSurface(new_srf, &px_format, 0)))
	{
		ft_putstr(SDL_GetError());
		ft_putchar('\n');
		env->err_id = INVALID_RESOURCE;
		return (NULL);
	}
	if (new_srf)
		SDL_FreeSurface(new_srf);
	return (convert_srf);
}

static void			init_cam(t_cam *cam)
{
	ft_bzero(cam, sizeof(t_cam));
	cam->dir.x = -1;
	cam->plane.y = 0.66;
	cam->center.x = WIN_WIDTH >> 1;
	cam->center.y = WIN_HEIGHT >> 1;
	cam->zoom = 1;
	cam->min_wall_dist = 2.5;
}

static void			init_img_tex(t_env *env, SDL_Surface **img_tex)
{
	img_tex[0] = load_surface(env, "resource/textures/eagle.png");
	img_tex[1] = load_surface(env, "resource/textures/red_brick.png");
	img_tex[2] = load_surface(env, "resource/textures/purple_stone.png");
	img_tex[3] = load_surface(env, "resource/textures/grey_stone.png");
	img_tex[4] = load_surface(env, "resource/textures/blue_stone.png");
	img_tex[5] = load_surface(env, "resource/textures/mossy.png");
	img_tex[6] = load_surface(env, "resource/textures/wood.png");
	img_tex[7] = load_surface(env, "resource/textures/color_stone.png");
}

static t_env		*env_def_val(t_env *env)
{
	if (!env)
		return (NULL);
	env->err_id = 0;
	ft_bzero(&env->flags, sizeof(t_flags));
	env->flags.is_compass_texture = 1;
	env->flags.mode = 2;
	init_cam(&env->cam);
	ft_bzero(&env->fps, sizeof(t_fps));
	env->fps.frame_limit_second = 1000 / FRAME_LIMIT;
	env->bytes_per_pixel = sizeof(Uint32);
	env->bits_per_pixel = env->bytes_per_pixel * (unsigned char)8;
	env->win_height_x128 = WIN_HEIGHT * 128;
	generate_texture(env);
	SDL_SetRelativeMouseMode(SDL_TRUE);
	init_img_tex(env, env->img_tex);
	if (env->err_id)
		return (NULL);
	env->txt.color = (SDL_Color){255, 255, 255, 0};
	env->txt.width = 0;
	env->txt.height = 0;
	return (env);
}

t_env				*init_env(void)
{
	t_env	*env;

	if ((!(env = (t_env *)malloc(sizeof(t_env)))
		&& (env->map.height = 0))
	|| SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_EVENTS)
	|| TTF_Init() || !IMG_Init(IMG_INIT_PNG)
	|| !(env->window = SDL_CreateWindow(WIN_NAME, SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED, WIN_WIDTH, WIN_HEIGHT, SDL_WINDOW_RESIZABLE))
	|| !(env->renderer = SDL_CreateRenderer(env->window, -1,
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC))
	|| !(env->screen = SDL_CreateTexture(env->renderer,
		SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_TARGET,
		WIN_WIDTH, WIN_HEIGHT))
	|| !(env->state = SDL_GetKeyboardState(&env->state_arr_length))
	|| !(env->img_tex = malloc(sizeof(SDL_Surface *) * TEXTURES))
	|| !(env->txt.font = TTF_OpenFont(DEF_FONT, DEF_FONT_SIZE))
	|| (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	|| !(env->music = Mix_LoadMUS("resource/sounds/horst_wessel_lied.wav"))
	|| !(env_def_val(env)))
	{
		quit_program(env);
		return (NULL);
	}
	return (env);
}
