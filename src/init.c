/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/22 17:23:17 by dromanic          #+#    #+#             */
/*   Updated: 2018/10/18 16:18:14 by dromanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"


//#include "../library/frameworks/SDL2_image.framework/Headers/SDL_image.h"

//static t_param	*init_param(void)
//{
//	t_param *new_param;
//
//	if ((new_param = (t_param *)malloc(sizeof(t_param))))
//	{
//		new_param->ratio = (int)(WIN_WIDTH / WIN_HEIGHT);
//		new_param->center_x = (int)(WIN_WIDTH / 2);
//		new_param->center_y = (int)(WIN_HEIGHT / 2);
//		new_param->cores = ft_get_processors_num();
//		new_param->threads = new_param->cores;
//		new_param->spec_step = 1;
//		new_param->offset_step = 0.5;
//		new_param->fr_depth_step = 1;
//		new_param->actial_zoom = 50;
//		new_param->offset_x = 0;
//		new_param->offset_y = 0;
//		new_param->i_mouse_move_seed = 0;
//		new_param->r_mouse_move_seed = 0;
//		new_param->alpha_shift = 0;
//		new_param->red_shift = 0;
//		new_param->green_shift = 0;
//		new_param->blue_shift = 0;
//	}
//	return (new_param);
//}

//int				flag_reset(t_flags *flags)
//{
//	if (!flags)
//		return (0);
//	ft_bzero(flags, sizeof(t_flags));
//	return (1);
//}

//static t_flags	*init_flags(void)
//{
//	t_flags	*new_flags;
//
//	if ((new_flags = (t_flags *)malloc(sizeof(t_flags))))
//		flag_reset(new_flags);
//	return (new_flags);
//}
SDL_Surface		*load_surface( char *path_name )
{
	SDL_Surface			*new_srf;
	SDL_Surface			*convert_srf;
	SDL_PixelFormat		px_format;

	new_srf = NULL;
	px_format.format = SDL_PIXELFORMAT_ARGB8888;
	px_format.palette = NULL;
	px_format.BytesPerPixel = sizeof(Uint32);
	px_format.BitsPerPixel = px_format.BytesPerPixel * (Uint8)8;
	px_format.Rmask = 0;
	px_format.Gmask = 0;
	px_format.Bmask = 0;
	px_format.Amask = 0;
	if (!(new_srf = IMG_Load(path_name))
	|| !(convert_srf = SDL_ConvertSurface(new_srf, &px_format, 0))
	)
	{
		ft_putstr(SDL_GetError());
		return (0);
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
//	new_text.messageFont = TTF_OpenFont(DEF_FONT, DEF_FONT_SIZE)
//}

t_env		*env_def_val(t_env *env)
{
	if (!env)
		return (NULL);
	env->game_over = false;
	env->is_compass_texture = 1;
	env->tex_mode = 2; //need to switch this in realtime (and correctly free)
	env->cam.pos.x = 22;
	env->cam.pos.y = 11.5;
	env->cam.dir.x = -1;
	env->cam.dir.y = 0;
	env->cam.plane.x = 0;//need to change in real time (give psihodelic effect)
	env->cam.plane.y = 0.66; //the 2d raycaster version of camera plane
	env->fps.current_tick = 0; //current_tick of current frame
	env->fps.previous_tick = 0; //current_tick of previous frame
	env->cam.center.x = WIN_WIDTH / 2;
	env->cam.center.y = WIN_HEIGHT / 2;
	env->fps.frame_limit_second = 1000 / FRAME_LIMIT;
	env->cam.zoom = 1;
	env->bytes_per_pixel = sizeof(Uint32);
	env->bits_per_pixel = env->bytes_per_pixel * (unsigned char)8;
	env->cam.wall_scale = 1;
	generate_texture(env);
	env->surfaces[0] = load_surface("textures/eagle.png");
	env->surfaces[1] = load_surface("textures/red_brick.png");
	env->surfaces[2] = load_surface("textures/purple_stone.png");
	env->surfaces[3] = load_surface("textures/grey_stone.png");
	env->surfaces[4] = load_surface("textures/blue_stone.png");
	env->surfaces[5] = load_surface("textures/mossy.png");
	env->surfaces[6] = load_surface("textures/wood.png");
	env->surfaces[7] = load_surface("textures/color_stone.png");
	env->surfaces[8] = load_surface("textures/color_stone.png");
	env->txt.color = (SDL_Color){255, 255, 255, 0};
	env->txt.width = 0;
	env->txt.height = 0;
//	env->map_height = 24;
//	env->map_width = 24;
	env->cam.min_wall_dist = 2.5;
	return (env);
}

t_env	*init_env(void)
{
	t_env	*new_env;

	if (!(new_env = (t_env *)malloc(sizeof(t_env)))
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
			(SDL_Surface **)malloc(sizeof(SDL_Surface *) * texture_count))
	|| !(new_env->txt.messageFont = TTF_OpenFont(DEF_FONT, DEF_FONT_SIZE))
	|| !(env_def_val(new_env)))
	{
		ft_putstr(TTF_GetError());
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
