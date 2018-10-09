/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/22 14:33:57 by dromanic          #+#    #+#             */
/*   Updated: 2018/10/08 18:31:19 by dromanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

Sint32	chose_color(Sint32 switch_num, Sint32 side)
{
	Sint32 color;
	//printf("%d\n", switch_num);
	if (switch_num == 1)
		color = RED;//0xFF << 16;
		// SDL_MapRGB(env->surface->format, 255, 0, 0);/ red
	else if (switch_num == 2)
		color = GREEN;//0xFF << 8;
		// SDL_MapRGB(env->surface->format, 0, 255, 0);// green
	else if (switch_num == 3)
		color = BLUE;//0xFF << 4;
		// SDL_MapRGB(env->surface->format, 0, 0, 255); blue
	else if (switch_num == 4)
		color = WHITE;//0xFFFFFF << 2;
		// SDL_MapRGB(env->surface->format, 255, 255, 255);//white
	else
		color = YELLOW;// 0xFFFF << 8;//SDL_MapRGB(env->surface->format, 255,
				// 255, 0);
		// yellow 0xFFff << 8
	if (side == 1) 				//give x and y sides different brightness
		color = color / 2;
//	printf("=%lu=", sizeof(int));
	return (color);
}