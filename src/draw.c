/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/21 20:43:55 by dromanic          #+#    #+#             */
/*   Updated: 2018/10/08 18:49:55 by dromanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

//void		redraw(t_env *env, int img_only)
//{
//	mlx_clear_window(env->mlx_ptr, env->win_ptr);
//	mlx_put_image_to_window(env->mlx_ptr, env->win_ptr,
//							env->img->ptr, 0, 0);
//	if (!env->flags->menu_off)
//		show_menu(env, 20, 10, env->flags);
//	if (!env->flags->hints_off)
//		show_combo(env, 20, 10);
//	if (!env->flags->values_off)
//		show_values(env, 20, 10);
//	if (img_only)
//		return ;
//	if (env->param->fr_id == FR_BARNSLEY)
//	{
//		clear_img(env);
//		draw_barnsley(env, env->param);
//	}
//	else
//		parallel_draw_fractal(env);
//}

void	clear_img_buff(t_env *env)
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
		{
			env->img_buff[y][x] = 0x0;
			x++;
		}
		y++;
	}
}

void	frame_limit(Uint32 current_tick, Uint32 previous_tick)
{
	if ((1000 / FRAME_LIMIT) > current_tick - previous_tick)
		SDL_Delay(1000 / FRAME_LIMIT - (current_tick - previous_tick));
}