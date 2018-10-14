/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/22 14:33:57 by dromanic          #+#    #+#             */
/*   Updated: 2018/10/14 20:01:12 by dromanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

Uint32	chose_color(Uint32 switch_num, bool side)
{
	Uint32	color; //printf("%d\n", switch_num);
	if (switch_num == 1)
		color = RED;//0xFF << 16;
	else if (switch_num == 2)
		color = GREEN;//0xFF << 8;
	else if (switch_num == 3)
		color = BLUE;//0xFF << 4;
	else if (switch_num == 4)
		color = WHITE;//0xFFFFFF << 2;
	else
		color = YELLOW;// 0xFFFF << 8;
	if (side) 				//give x and y sides different brightness
		color /= 2;
//	printf("=%lu=", sizeof(int));
	return (color);
}

void	generate_texture(t_env *env)
{
	Uint32	x;
	Uint32	y;
	Uint32	px;

	x = 0;
	while (x < tex_width)
	{
		y = 0;
		while (y < tex_height)
		{
			px = tex_width * y + x;
			Sint32 xorcolor = (x * 256 / tex_width) ^ (y * 256 / tex_height);
			//int xcolor = x * 256 / tex_width;
			Sint32 ycolor   = y * 256 / tex_height;
			Sint32 xycolor  = y * 128 / tex_height + x * 128 / tex_width;
			env->texture[0][px] = 65536 * 254 * (x != y && x != tex_width - y); //flat red sdl_texture with black cross
			env->texture[1][px] = xycolor + 256 * xycolor + 65536 * xycolor; //sloped greyscale
			env->texture[2][px] = 256 * xycolor + 65536 * xycolor; //sloped yellow gradient
			env->texture[3][px] = xorcolor + 256 * xorcolor + 65536 * xorcolor; //xor greyscale
			env->texture[4][px] = 256 * xorcolor; //xor green
			env->texture[5][px] = 65536 * 192 * (x % 16 && y % 16); //red bricks
			env->texture[6][px] = 65536 * ycolor; //red gradient
			env->texture[7][px] = 128 + 256 * 128 + 65536 * 128; //flat grey sdl_texture
			y++;
		}
		x++;
	}
}
