/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/22 14:33:57 by dromanic          #+#    #+#             */
/*   Updated: 2018/10/23 15:08:03 by dromanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

Uint32			chose_color(Uint32 switch_num, bool side)
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

static void		set_textures(t_env *env, Uint32 x, Uint32 y, Uint32 px)
{
	Uint32 y_col;
	Uint32 xy_col;
	Uint32 xor_col;

	xor_col = (x * 256 / TEX_WIDTH) ^ (y * 256 / TEX_HEIGHT);
	y_col = y * 256 / TEX_HEIGHT;
	xy_col = y * 128 / TEX_HEIGHT + x * 128 / TEX_WIDTH;
	env->gen_tex[0][px] =
		(Uint32)(65536 * 254 * (x != y && x != TEX_WIDTH - y));
	env->gen_tex[1][px] = xy_col + 256 * xy_col + 65536 * xy_col;
	env->gen_tex[2][px] = 256 * xy_col + 65536 * xy_col;
	env->gen_tex[3][px] = xor_col + 256 * xor_col + 65536 * xor_col;
	env->gen_tex[4][px] = 256 * xor_col;
	env->gen_tex[5][px] = (Uint32)(65536 * 192 * (x % 16 && y % 16));
	env->gen_tex[6][px] = 65536 * y_col;
	env->gen_tex[7][px] = 128 + 256 * 128 + 65536 * 128;
}

void			generate_texture(t_env *env)
{
	Uint32	x;
	Uint32	y;

	x = (Uint32)-1;
	while (++x < TEX_WIDTH)
	{
		y = (Uint32)-1;
		while (++y < TEX_HEIGHT)
			set_textures(env, x, y, TEX_WIDTH * y + x);
	}
}
