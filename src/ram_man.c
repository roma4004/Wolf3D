/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ram_man.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/02 12:59:00 by dromanic          #+#    #+#             */
/*   Updated: 2018/10/02 13:04:54 by dromanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	free_env(t_env *env)
{
	if (env)
	{
		SDL_DestroyTexture(env->mainTexture);
		SDL_DestroyRenderer(env->renderer);
		SDL_DestroyWindow(env->window);
	}
}