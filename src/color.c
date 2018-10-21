/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/22 14:33:57 by dromanic          #+#    #+#             */
/*   Updated: 2018/10/21 14:42:21 by dromanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

Uint32	chose_color(Uint32 switch_num, bool side)
{
	Uint32	color;

	if (switch_num == 1)
		color = RED;
	else if (switch_num == 2)
		color = GREEN;
	else if (switch_num == 3)
		color = BLUE;
	else if (switch_num == 4)
		color = WHITE;
	else
		color = YELLOW;
	if (side)
		color /= 2;
	return (color);
}

void	generate_texture(t_env *env)
{
	Uint32	x;
	Uint32	y;
	Uint32	px;

	x = (Uint32)-1;
	while (++x < TEX_WIDTH)
	{
		y = (Uint32)-1;
		while (++y < TEX_HEIGHT)
		{
			px = TEX_WIDTH * y + x;
			Uint32 xorcolor = (x * 256 / TEX_WIDTH) ^ (y * 256 / TEX_HEIGHT);
			Uint32 ycolor   = y * 256 / TEX_HEIGHT;
			Uint32 xycolor  = y * 128 / TEX_HEIGHT + x * 128 / TEX_WIDTH;
			env->gen_tex[0][px] =
					(Uint32)(65536 * 254 * (x != y && x != TEX_WIDTH - y));
			env->gen_tex[1][px] = xycolor + 256 * xycolor + 65536 * xycolor;
			env->gen_tex[2][px] = 256 * xycolor + 65536 * xycolor;
			env->gen_tex[3][px] = xorcolor + 256 * xorcolor + 65536 * xorcolor;
			env->gen_tex[4][px] = 256 * xorcolor;
			env->gen_tex[5][px] = (Uint32)(65536 * 192 * (x % 16 && y % 16));
			env->gen_tex[6][px] = 65536 * ycolor;
			env->gen_tex[7][px] = 128 + 256 * 128 + 65536 * 128;
		}
	}
}
