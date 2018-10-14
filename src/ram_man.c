/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ram_man.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/02 12:59:00 by dromanic          #+#    #+#             */
/*   Updated: 2018/10/10 15:20:32 by dromanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	quit_program(t_env *env)
{
	if (env)
	{
		if (env->screen_texture)
		{
			SDL_DestroyTexture(env->screen_texture);
			env->screen_texture = NULL;
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
		SDL_Quit();
	}
}