/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/22 15:22:29 by dromanic          #+#    #+#             */
/*   Updated: 2018/10/23 14:53:43 by dromanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void		move(t_cam *cam, Uint32 **map, double dir_x, double dir_y)
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

static void		rotate_x(t_cam *cam, double angle,
							double old_dir_x, double old_plane_x)
{
	cam->dir.x = cam->dir.x * cos(angle) - cam->dir.y * sin(angle);
	cam->dir.y = old_dir_x * sin(angle) + cam->dir.y * cos(angle);
	cam->plane.x = cam->plane.x * cos(angle) - cam->plane.y * sin(angle);
	cam->plane.y = old_plane_x * sin(angle) + cam->plane.y * cos(angle);
}

static void		mouse_events(SDL_Event *event, t_cam *cam)
{
	if (event->type == SDL_MOUSEMOTION)
	{
		if (event->motion.xrel < 0)
			rotate_x(cam, -event->motion.xrel / 1000.0,
						cam->dir.x, cam->plane.x);
		else if (event->motion.xrel > 0)
			rotate_x(cam, event->motion.xrel / -1000.0,
						cam->dir.x, cam->plane.x);
		else
			event->motion.xrel = 0;
	}
	if (event->type == SDL_MOUSEWHEEL)
	{
		if (event->wheel.y > 0 && cam->zoom < 10)
			cam->zoom += 0.1;
		else if (event->wheel.y < 0 && cam->zoom > 1)
			cam->zoom -= 0.1;
	}
	if (event->type == SDL_MOUSEBUTTONUP
	&& event->button.button == SDL_BUTTON_MIDDLE)
		cam->zoom = 1;
}

static void		keyboard_evens(SDL_Event *event, SDL_Keycode key,
								t_flags *flags)
{
	bool	*flag;

	if (event->type == SDL_KEYDOWN
		&& ((key == SDLK_ESCAPE && (flag = &flags->is_game_over))
			|| (key == SDLK_w && (flag = &flags->is_move_forward))
			|| (key == SDLK_s && (flag = &flags->is_move_backward))
			|| (key == SDLK_a && (flag = &flags->is_strafe_left))
			|| (key == SDLK_d && (flag = &flags->is_strafe_right))
			|| (key == SDLK_q && (flag = &flags->is_rotate_left))
			|| (key == SDLK_e && (flag = &flags->is_rotate_right))))
		*flag = true;
	if (event->type == SDL_KEYUP && key == SDLK_2 && flags->mode++ >= 2)
		flags->mode = 0;
	if (event->type == SDL_KEYUP && key == SDLK_1)
		flags->is_compass_texture = (flags->is_compass_texture) ? false : true;
	if (event->type == SDL_KEYUP
		&& ((key == SDLK_ESCAPE && (flag = &flags->is_game_over))
			|| (key == SDLK_w && (flag = &flags->is_move_forward))
			|| (key == SDLK_s && (flag = &flags->is_move_backward))
			|| (key == SDLK_a && (flag = &flags->is_strafe_left))
			|| (key == SDLK_d && (flag = &flags->is_strafe_right))
			|| (key == SDLK_q && (flag = &flags->is_rotate_left))
			|| (key == SDLK_e && (flag = &flags->is_rotate_right))))
		*flag = false;
}

void			event_handler(t_env *env, t_cam *cam, t_flags *flags)
{
	int sign;

	while (SDL_PollEvent(&env->event))
	{
		if (env->event.type == SDL_QUIT)
			flags->is_game_over = true;
		mouse_events(&env->event, cam);
		keyboard_evens(&env->event, env->event.key.keysym.sym, flags);
	}
	if ((flags->is_move_forward == true && (sign = 1))
	|| (flags->is_move_backward == true && (sign = -1)))
		move(cam, env->map.tex_id, cam->dir.x * sign, cam->dir.y * sign);
	if ((flags->is_strafe_left == true && (sign = -1))
	|| (flags->is_strafe_right == true && (sign = 1)))
		move(cam, env->map.tex_id, cam->plane.x * sign, cam->plane.y * sign);
	if ((flags->is_rotate_left == true && (sign = 1))
	|| (flags->is_rotate_right == true && (sign = -1)))
		rotate_x(cam, cam->rotate_speed * sign, cam->dir.x, cam->plane.x);
}
