/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interface.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/24 14:48:59 by dromanic          #+#    #+#             */
/*   Updated: 2018/10/08 17:33:24 by dromanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int		display_interface(t_env *env)
{
	TTF_Font	*messageFont = TTF_OpenFont(DEF_FONT, 24);

	if (messageFont == NULL) {
		printf("%s\n", SDL_GetError());
		SDL_Quit();
		return 1;
	}
	env->game_over = false;
	ft_memset(env->framesTimes, 0, sizeof(env->framesTimes));
	env->frameCount = 0;
	env->frameTimeLast = SDL_GetTicks();
	return (0);
}