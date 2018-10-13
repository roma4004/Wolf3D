/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interface.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/24 14:48:59 by dromanic          #+#    #+#             */
/*   Updated: 2018/10/13 12:32:32 by dromanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int		display_interface(void)
{
	TTF_Font	*messageFont = TTF_OpenFont(DEF_FONT, 24);

	if (messageFont == NULL) {
		printf("%s\n", SDL_GetError());
		SDL_Quit();
		return 1;
	}
	return (0);
}