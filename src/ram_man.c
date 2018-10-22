/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ram_man.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/02 12:59:00 by dromanic          #+#    #+#             */
/*   Updated: 2018/10/22 11:41:21 by dromanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void		clear_img_buff(t_env *env)
{
	Uint32	y;
	Uint32	x;

	if (!env)
		return ;
	y = 0;
	while (y < WIN_HEIGHT)
	{
		x = 0;
		while (x < WIN_WIDTH)
			env->img_buff[y][x++] = 0x0;
		y++;
	}
}

void	quit_program(t_env *env)
{
	if (env)
	{
		if (env->screen)
		{
			SDL_DestroyTexture(env->screen);
			env->screen = NULL;
		}
		if (env->renderer)
		{
			SDL_DestroyRenderer(env->renderer);
			env->renderer = NULL;
		}
		if (env->window)
		{
			SDL_DestroyWindow(env->window);
			env->window = NULL;
		}
		if (env->surface)
		{
			SDL_FreeSurface(env->surface);
			env->surface = NULL;
		}
		if (env->music)
		{
			Mix_CloseAudio();
		}
		ft_putstr(SDL_GetError());
		show_errors(env);
		SDL_Quit();
	}
}