/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/18 17:13:08 by dromanic          #+#    #+#             */
/*   Updated: 2018/10/23 17:53:04 by dromanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void		frame_rate_adjustment(t_env *env, t_fps *fps)
{
	fps->pre_tick = fps->cur_tick;
	fps->cur_tick = SDL_GetTicks();
	fps->frame_time = (fps->cur_tick - fps->pre_tick) / 1000.0f;
	fps->value = (u_char)(1.0 / fps->frame_time);
	env->cam.move_speed = fps->frame_time * 3;
	env->cam.rotate_speed = fps->frame_time * 2;
	if ((fps->frame_limit_second) > fps->cur_tick - fps->pre_tick)
		SDL_Delay(fps->frame_limit_second - (fps->cur_tick - fps->pre_tick));
}

int				main(int argc, char **argv)
{
	t_env	*env;

	if ((env = init_env()) && argc == 2 && parse_map(argv[1], env)
		&& !Mix_PlayMusic(env->music, 1))
		while (!env->flags.is_game_over)
		{
			frame_rate_adjustment(env, &env->fps);
			event_handler(env, &env->cam, &env->flags);
			clear_img_buff(env);
			raycasting(env, env->map.tex_id);
			SDL_UpdateTexture(env->screen, NULL, env->img_buff, WIN_WIDTH << 2);
			SDL_RenderCopy(env->renderer, env->screen, NULL, NULL);
			if (FPS)
				render_interface(env, &env->fps, &env->txt);
			SDL_RenderPresent(env->renderer);
		}
	if (env)
		quit_program(env);
	return (0);
}
