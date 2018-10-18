/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/22 15:22:29 by dromanic          #+#    #+#             */
/*   Updated: 2018/10/18 18:03:06 by dromanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void	move(t_cam *cam, Uint32 worldMap[mapWidth][mapHeight],
					double dir_x, double dir_y)
{
	Uint32 x;
	Uint32 y;

	x = (Uint32)(cam->pos.x + dir_x * cam->move_speed * cam->min_wall_dist);
	y = (Uint32)cam->pos.y;
	if (!worldMap[x][y])
		cam->pos.x += dir_x * cam->move_speed;
	x = (Uint32)cam->pos.x;
	y = (Uint32)(cam->pos.y + dir_y * cam->move_speed * cam->min_wall_dist);
	if (!worldMap[x][y])
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

void		event_handler(t_env *env, Uint32 worldMap[mapWidth][mapHeight])
{
	SDL_PumpEvents();
	SDL_PollEvent(&env->event);

	if (env->event.type == SDL_QUIT || env->state[SDL_SCANCODE_ESCAPE])
		env->game_over = true;
	if (env->state[SDL_SCANCODE_W])
		move(&env->cam, worldMap, env->cam.dir.x, env->cam.dir.y);
	if (env->state[SDL_SCANCODE_S])
		move(&env->cam, worldMap, -env->cam.dir.x, -env->cam.dir.y);
	if	(env->state[SDL_SCANCODE_A])
		move(&env->cam, worldMap, -env->cam.plane.x, -env->cam.plane.y);
	if (env->state[SDL_SCANCODE_D])
		move(&env->cam, worldMap, env->cam.plane.x, env->cam.plane.y);
	if (env->state[SDL_SCANCODE_E])
		rotate_x_cam(&env->cam, -env->cam.rotate_speed,
						env->cam.dir.x, env->cam.plane.x);
	if (env->state[SDL_SCANCODE_Q])
		rotate_x_cam(&env->cam, env->cam.rotate_speed,
						env->cam.dir.x, env->cam.plane.x);
}