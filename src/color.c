/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/22 14:33:57 by dromanic          #+#    #+#             */
/*   Updated: 2018/10/11 14:30:30 by dromanic         ###   ########.fr       */
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

void	generate_texture(t_env *env)
{
	Sint32 x;
	Sint32 y;

	x = -1;
	y = -1;
	while (++x < texWidth)
	{
		while (++y < texHeight)
		{
			Sint32 xorcolor = (x * 256 / texWidth) ^ (y * 256 / texHeight);
			//int xcolor = x * 256 / texWidth;
			Sint32 ycolor = y * 256 / texHeight;
			Sint32 xycolor = y * 128 / texHeight + x * 128 / texWidth;
			env->texture[0][texWidth * y + x] = 65536 * 254 * (x != y && x != texWidth - y); //flat red
			// sdl_texture with black cross
			env->texture[1][texWidth * y + x] = xycolor + 256 * xycolor + 65536 * xycolor; //sloped greyscale
			env->texture[2][texWidth * y + x] = 256 * xycolor + 65536 * xycolor; //sloped yellow gradient
			env->texture[3][texWidth * y + x] = xorcolor + 256 * xorcolor + 65536 * xorcolor; //xor greyscale
			env->texture[4][texWidth * y + x] = 256 * xorcolor; //xor green
			env->texture[5][texWidth * y + x] = 65536 * 192 * (x % 16 && y % 16); //red bricks
			env->texture[6][texWidth * y + x] = 65536 * ycolor; //red gradient
			env->texture[7][texWidth * y + x] = 128 + 256 * 128 + 65536 * 128; //flat grey sdl_texture
		}
	}
}
