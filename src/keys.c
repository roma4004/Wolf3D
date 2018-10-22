/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/22 15:22:29 by dromanic          #+#    #+#             */
/*   Updated: 2018/10/22 21:58:05 by dromanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	move(t_cam *cam, Uint32 **map, double dir_x, double dir_y)
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

void	rotate_x(t_cam *cam, double angle, double old_dir_x, double old_plane_x)
{
	cam->dir.x = cam->dir.x * cos(angle) - cam->dir.y * sin(angle);
	cam->dir.y = old_dir_x * sin(angle) + cam->dir.y * cos(angle);
	cam->plane.x = cam->plane.x * cos(angle) - cam->plane.y * sin(angle);
	cam->plane.y = old_plane_x * sin(angle) + cam->plane.y * cos(angle);
}

void		mouse_events(SDL_Event *event, t_cam *cam)
{
//	ft_putstr(SDL_GetError());
//	SDL_ClearError();
	if (event->type == SDL_MOUSEMOTION)
	{


		if (event->type == SDL_MOUSEMOTION)
		{
			printf("Mouse move");
		}
		if (event->motion.xrel > 3)
		{
//			my_event->type           = SDL_KEYDOWN;
//			my_event->key.keysym.sym = SDLK_e;
//			SDL_PushEvent(my_event);
//			env->state[SDL_SCANCODE_Q] = true;

		rotate_x(cam, -cam->rotate_speed, cam->dir.x, cam->plane.x);

		}
		if (event->motion.xrel < -3)
		{
			//			my_event->type           = SDL_KEYDOWN;
//			my_event->key.keysym.sym = SDLK_q;
//			my_event->key.keysym.scancode = SDL_SCANCODE_Q;
//			SDL_PushEvent(my_event);
//			env->state[SDL_SCANCODE_E] = true;
			rotate_x(cam, cam->rotate_speed, cam->dir.x, cam->plane.x);

		}
		event->motion.xrel = 0;
	}
	if (event->type == SDL_MOUSEWHEEL)
	{
		if(event->wheel.y > 0 && cam->zoom < 10)
			cam->zoom += 0.1;
		else if(event->wheel.y < 0 && cam->zoom > 1)
			cam->zoom -= 0.1;
	}
}



void		keyboard_evens(t_env *env, SDL_Keysym *keysym, t_cam *cam)
{
	bool	*flag;

	if (env->event.type == SDL_QUIT)
		env->game_over = true;
	if (env->event.type == SDL_KEYDOWN)
	{
		if (((keysym->sym == SDLK_ESCAPE && (flag = &env->game_over))
		|| ((keysym->sym == SDLK_w) && (flag = &cam->move_forward))
		|| ((keysym->sym == SDLK_s) && (flag = &cam->move_backward))
		|| ((keysym->sym == SDLK_a) && (flag = &cam->strafe_left))
		|| ((keysym->sym == SDLK_d) && (flag = &cam->strafe_right))
		|| ((keysym->sym == SDLK_q) && (flag = &cam->rotate_left))
		|| ((keysym->sym == SDLK_e) && (flag = &cam->rotate_right))))
			*flag = true;
	}
	if (env->event.type == SDL_KEYUP)
	{
		if (keysym->sym == SDLK_w)
			env->cam.move_forward = false;
		if (keysym->sym == SDLK_s)
			env->cam.move_backward = false;
		if (keysym->sym == SDLK_a)
			env->cam.strafe_left = false;
		if (keysym->sym == SDLK_d)
			env->cam.strafe_right = false;
		if (keysym->sym == SDLK_q)
			env->cam.rotate_left = false;
		if (keysym->sym == SDLK_e)
			env->cam.rotate_right = false;
	}

//	if (((state[SDL_SCANCODE_E]
//		|| env->my_event.key.keysym.sym == SDLK_e) && (sign = -1))
//	|| (state[SDL_SCANCODE_Q] && (sign = 1)))
//	{
//		rotate_x(cam, cam->rotate_speed * sign, cam->dir.x, cam->plane.x);
//		env->my_event.key.keysym.sym = false;
//	}
//	if ((state[SDL_SCANCODE_W] && (sign = 1))
//	|| (state[SDL_SCANCODE_S] && (sign = -1)))
//		move(cam, env->map.tex_id, cam->dir.x * sign, cam->dir.y * sign);
//	if	((state[SDL_SCANCODE_A] && (sign = -1))
//	||	(state[SDL_SCANCODE_D] && (sign = 1)))
//		move(cam, env->map.tex_id, cam->plane.x * sign, cam->plane.y * sign);
//	if (state[SDL_SCANCODE_1])
//	{
//		env->is_compass_texture = (env->is_compass_texture) ? false : true;
//		SDL_Delay(42);
//	}
//	if (state[SDL_SCANCODE_2])
//	{
//		if (env->mode++ >= 2)
//			env->mode = 0;
//		SDL_Delay(42);
//	}

}

void			event_handler(t_env *env, t_cam *cam)
{
	int sign;

	while (SDL_PollEvent(&env->event))
	{
		mouse_events(&env->event, cam);
		keyboard_evens(env, &env->event.key.keysym, &env->cam);
	}
	if ((env->cam.move_forward == true && (sign = 1))
	|| (env->cam.move_backward == true && (sign = -1)))
		move(cam, env->map.tex_id, cam->dir.x * sign, cam->dir.y * sign);
	if ((env->cam.strafe_left == true && (sign = -1))
	|| (env->cam.strafe_right == true && (sign = 1)))
		move(cam, env->map.tex_id, cam->plane.x * sign, cam->plane.y * sign);
	if ((env->cam.rotate_left == true && (sign = 1))
	|| (env->cam.rotate_right == true && (sign = -1)))
		rotate_x(cam, cam->rotate_speed * sign, cam->dir.x, cam->plane.x);
//////	SDL_FlushEvents();
//	SDL_FlushEvent(SDL_MOUSEMOTION);
//	SDL_FlushEvent(SDL_KEYDOWN);

}