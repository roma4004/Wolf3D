/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/22 17:23:17 by dromanic          #+#    #+#             */
/*   Updated: 2018/10/10 15:43:38 by dromanic         ###   ########.fr       */
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
SDL_Texture		*load_texture(t_env *env, char *path_name )
{
	SDL_Surface *new_srf;
	SDL_Texture *new_tex;

	//	||	!(new_tex = // SDL_CreateTextureFromSurface(env->renderer, new_srf))
	if (!(new_srf = SDL_LoadBMP(path_name))
	||	!(new_tex = IMG_LoadTexture(env->renderer, path_name))
	)
	{
		ft_putstr(TTF_GetError());
		return (0);
	}
	;
	SDL_FreeSurface(new_srf);
	return (new_tex);
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

t_env	*init_env(void)
{
	t_env	*new_env;

	if ((new_env = (t_env *)malloc(sizeof(t_env))))
	{
		if ((SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_EVENTS) < 0)//OR SDL_INIT_EVERYTHING
		|| (TTF_Init() == -1)
		|| (!(new_env->window =
				SDL_CreateWindow(WIN_NAME, SDL_WINDOWPOS_UNDEFINED,   //SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
					SDL_WINDOWPOS_UNDEFINED, WIN_WIDTH, WIN_HEIGHT,
						SDL_WINDOW_RESIZABLE))) 	//SDL_WINDOW_FULLSCREEN ||
						// SDL_WINDOW_RESIZABLE
		|| !(new_env->renderer = SDL_CreateRenderer(new_env->window, -1,
				SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC))
//		|| !(new_env->mainTexture =
//				SDL_CreateTexture(new_env->renderer, SDL_PIXELFORMAT_ARGB8888,
//						SDL_TEXTUREACCESS_STATIC, WIN_WIDTH, WIN_HEIGHT))
		|| (SDL_GetDesktopDisplayMode(0, &new_env->display_param))
		|| (new_env->game_over = false)
		//|| !(new_env->img_buff =
		//		init_img_buff((uint32_t)WIN_WIDTH, (uint32_t)WIN_HEIGHT))
		|| !(new_env->state = SDL_GetKeyboardState(&new_env->state_arr_length))
		|| !( IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)
		|| (new_env->surface = SDL_GetWindowSurface(new_env->window))
		)
		{
			ft_putstr(TTF_GetError());
			SDL_Quit();
			return (NULL);
		}
	}
	return (new_env);
}

//img_buff is not two dimensional
