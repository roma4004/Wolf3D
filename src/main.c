/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/18 17:13:08 by dromanic          #+#    #+#             */
/*   Updated: 2018/10/21 21:30:41 by dromanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	show_errors(t_env *env)
{
	if (env->error_num == 404)
		ft_putstr_fd("MAP_ERR", 2);
	if (env->error_num == 405)
		ft_putstr_fd("READ_ERR", 2);
	if (env->error_num == 406)
		ft_putstr_fd("WIDTH_ERR", 2);
	if (env->error_num == 407)
		ft_putstr_fd("INVALID_RESOURCE", 2);
	if (env->error_num == 408)
		ft_putstr_fd("408", 2);
	if (env->error_num && errno)
		ft_putstr_fd(" - ", 2);
	if (errno)
		ft_putstr_fd(strerror(errno), 2);
	if (env->error_num || errno)
		ft_putstr_fd("\n", 2);
}

size_t	ft_cnt_words(char *str, size_t max_i, char separator)
{
	size_t	i;
	size_t	num;

	if (str == NULL)
		return (0);
	i = 0;
	num = 0;
	if (str[0] != separator)
		num++;
	while (++i < max_i && str[i])
		if (str[i] != separator && str[i - 1] == separator)
			num++;
	return (num);
}

static void	frame_rate_adjustment(t_env *env, t_fps *fps)
{
	fps->previous_tick = fps->current_tick;
	fps->current_tick = SDL_GetTicks();
	fps->frame_time = (fps->current_tick - fps->previous_tick) / 1000.0f;
	fps->value = (u_char)(1.0 / fps->frame_time);
	env->cam.move_speed = fps->frame_time * 3; //in squares/second
	env->cam.rotate_speed = fps->frame_time * 2; //in radians/second
	env->cam.rotate_speed_mouse = fps->frame_time * 3; //in radians/second
	if ((fps->frame_limit_second) > fps->current_tick - fps->previous_tick)
		SDL_Delay(fps->frame_limit_second -
			(fps->current_tick - fps->previous_tick));
}

int			main(int argc, char **argv)
{
	t_env	*env;
	if ((env = init_env()) && argc == 2 && parse_map(argv[1], env)
		&& !Mix_PlayMusic(env->music, 1))
		while (!env->game_over)
		{
			SDL_RenderPresent(env->renderer);
			frame_rate_adjustment(env, &env->fps);
			clear_img_buff(env);
			raycasting(env, env->map.tex_id);
			SDL_UpdateTexture(env->screen, NULL, env->img_buff, WIN_WIDTH << 2);
			SDL_RenderCopy(env->renderer, env->screen, NULL, NULL);
			render_interface(env, &env->txt);
			event_handler(env, &env->cam);
		}
	if (env)
		quit_program(env);
	return (0);
}
