/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/22 15:22:29 by dromanic          #+#    #+#             */
/*   Updated: 2018/10/21 21:22:46 by dromanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void	move(t_cam *cam, Uint32 **map, double dir_x, double dir_y)
{
	Uint32 x;
	Uint32 y;

	x = (Uint32)(cam->pos.x + dir_x * cam->move_speed * cam->min_wall_dist);
	y = (Uint32)cam->pos.y;
	if (!map[x][y])
		cam->pos.x += dir_x * cam->move_speed;
	x = (Uint32)cam->pos.x;
	y = (Uint32)(cam->pos.y + dir_y * cam->move_speed * cam->min_wall_dist);
	if (!map[x][y])
		cam->pos.y += dir_y * cam->move_speed;
}

static void	rotate_x_cam(t_cam *cam, double rotate_speed,
							double old_dir_x, double old_plane_x)
{
	cam->dir.x =
			cam->dir.x * cos(rotate_speed) - cam->dir.y * sin(rotate_speed);
	cam->dir.y =
			old_dir_x * sin(rotate_speed) + cam->dir.y * cos(rotate_speed);
	cam->plane.x =
			cam->plane.x * cos(rotate_speed) - cam->plane.y * sin(rotate_speed);
	cam->plane.y =
			old_plane_x * sin(rotate_speed) + cam->plane.y * cos(rotate_speed);
}

static void		mouse_events(t_env *env, t_cam *cam)
{
	if (env->event.type != SDL_MOUSEMOTION)
		return ;
	if (env->event.motion.xrel > 3)
		rotate_x_cam(cam, -cam->rotate_speed_mouse, cam->dir.x, cam->plane.x);
	if (env->event.motion.xrel < -3)
		rotate_x_cam(cam, cam->rotate_speed_mouse, cam->dir.x, cam->plane.x);
	SDL_FlushEvent(SDL_MOUSEMOTION);
}

static void		keyboard_evens(t_env *env, t_cam *cam)
{
	if (env->event.type == SDL_QUIT || env->state[SDL_SCANCODE_ESCAPE])
		env->game_over = true;
	if (env->state[SDL_SCANCODE_W])
		move(&env->cam, env->map.tex_id, cam->dir.x, cam->dir.y);
	if (env->state[SDL_SCANCODE_S])
		move(&env->cam, env->map.tex_id, -cam->dir.x, -cam->dir.y);
	if	(env->state[SDL_SCANCODE_A])
		move(&env->cam, env->map.tex_id, -cam->plane.x, -cam->plane.y);
	if (env->state[SDL_SCANCODE_D])
		move(&env->cam, env->map.tex_id, cam->plane.x, cam->plane.y);
	if (env->state[SDL_SCANCODE_E])
		rotate_x_cam(&env->cam, -cam->rotate_speed, cam->dir.x, cam->plane.x);
	if (env->state[SDL_SCANCODE_Q])
		rotate_x_cam(&env->cam, cam->rotate_speed, cam->dir.x, cam->plane.x);
	if (env->state[SDL_SCANCODE_1])
	{
		env->is_compass_texture = (env->is_compass_texture) ? false : true;
		SDL_Delay(42);
	}
	if (env->state[SDL_SCANCODE_2])
	{
		if (env->mode++ >= 2)
			env->mode = 0;
		SDL_Delay(42);
	}
	SDL_FlushEvent(SDL_KEYDOWN);
}

void			event_handler(t_env *env, t_cam *cam)
{
	SDL_PollEvent(&env->event);
	keyboard_evens(env, cam);
	mouse_events(env, cam);
}
