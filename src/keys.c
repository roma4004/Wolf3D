/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/22 15:22:29 by dromanic          #+#    #+#             */
/*   Updated: 2018/10/15 15:53:40 by dromanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	event_handler(t_env *env, Uint32 worldMap[mapWidth][mapHeight])
{
	SDL_PumpEvents();
	SDL_PollEvent(&env->event);
	if (env->event.type == SDL_QUIT || env->state[SDL_SCANCODE_ESCAPE])
		env->game_over = true;
	if (env->state[SDL_SCANCODE_W]) // move forward if no wall
	{
		if (worldMap[(Uint32)(env->cam.pos.x + env->cam.dir.x * env->cam.move_speed)]
			[(Uint32)(env->cam.pos.y)] == false)
			env->cam.pos.x += env->cam.dir.x *env->cam.move_speed;
		if (worldMap[(Uint32)(env->cam.pos.x)]
			[(Uint32)(env->cam.pos.y + env->cam.dir.y *env->cam.move_speed)] == false)
			env->cam.pos.y += env->cam.dir.y *env->cam.move_speed;
	}
	if (env->state[SDL_SCANCODE_S]) //move backwards if no wall
	{
		if (worldMap[(Uint32)(env->cam.pos.x - env->cam.dir.x *env->cam.move_speed)]
			[(Uint32)(env->cam.pos.y)] == false)
			env->cam.pos.x -= env->cam.dir.x *env->cam.move_speed;
		if (worldMap[(Uint32)env->cam.pos.x]
			[(Uint32)(env->cam.pos.y - env->cam.dir.y *env->cam.move_speed)] == false)
			env->cam.pos.y -= env->cam.dir.y *env->cam.move_speed;
	}

	if	(env->state[SDL_SCANCODE_A]) // move forward if no wall
	{//both camera dir and camera plane must be rotated
//		double oldDirX = env->dir.x;
//		env->dir.x = env->dir.x * cos(env->cam.rotate_speed) - env->dir.y * sin(env->cam.rotate_speed);
//		env->dir.y = oldDirX * sin(env->cam.rotate_speed) + env->dir.y * cos(env->cam.rotate_speed);
//		double oldPlaneX = env->cam.plane.x;
//		env->cam.plane.x = env->cam.plane.x * cos(env->cam.rotate_speed) - env->cam.plane.y * sin(env->cam.rotate_speed);
//		env->cam.plane.y = oldPlaneX * sin(env->cam.rotate_speed) + env->cam.plane.y * cos(env->cam.rotate_speed);

		if (worldMap[(Uint32)(env->cam.pos.x + env->cam.dir.y *env->cam.move_speed)]
			[(Uint32)(env->cam.pos.y)] == false)
			env->cam.pos.x += env->cam.dir.y *env->cam.move_speed;
		if (worldMap[(Uint32)(env->cam.pos.x)]
			[(Uint32)(env->cam.pos.y + env->cam.dir.x *env->cam.move_speed)] == false)
			env->cam.pos.y += env->cam.dir.x *env->cam.move_speed;
	}
	if (env->state[SDL_SCANCODE_D]) //move backwards if no wall
	{
		if (worldMap[(Uint32)(env->cam.pos.x - env->cam.dir.y *env->cam.move_speed)]
			[(Uint32)(env->cam.pos.y)] == false)
			env->cam.pos.x -= env->cam.dir.y *env->cam.move_speed;
		if (worldMap[(Uint32)env->cam.pos.x]
			[(Uint32)(env->cam.pos.y - env->cam.dir.x *env->cam.move_speed)] == false)
			env->cam.pos.y -= env->cam.dir.x *env->cam.move_speed;
	}


	if (env->state[SDL_SCANCODE_E]) //rotate to the right
	{    //both camera dir and camera plane must be rotated
		float oldDirX = env->cam.dir.x;
		env->cam.dir.x = env->cam.dir.x * cos(-env->cam.rotate_speed)
						- env->cam.dir.y * sin(-env->cam.rotate_speed);
		env->cam.dir.y = oldDirX * sin(-env->cam.rotate_speed)
						+ env->cam.dir.y * cos(-env->cam.rotate_speed);
		float oldplanex = env->cam.plane.x;
		env->cam.plane.x = env->cam.plane.x * cos(-env->cam.rotate_speed)
					- env->cam.plane.y * sin(-env->cam.rotate_speed);
		env->cam.plane.y =
				oldplanex * sin(-env->cam.rotate_speed) + env->cam.plane.y * cos
						(-env->cam.rotate_speed);
	}
	if (env->state[SDL_SCANCODE_Q]) //rotate to the left
	{    //both camera dir and camera plane must be rotated
		double oldDirX = env->cam.dir.x;
		env->cam.dir.x = env->cam.dir.x * cos(env->cam.rotate_speed)
						- env->cam.dir.y * sin(env->cam.rotate_speed);
		env->cam.dir.y = oldDirX * sin(env->cam.rotate_speed)
				+ env->cam.dir.y * cos(env->cam.rotate_speed);
		double oldplanex = env->cam.plane.x;
		env->cam.plane.x = env->cam.plane.x * cos(env->cam.rotate_speed)
					- env->cam.plane.y * sin(env->cam.rotate_speed);
		env->cam.plane.y = oldplanex * sin(env->cam.rotate_speed)
					+ env->cam.plane.y * cos(env->cam.rotate_speed);
	}
}
//if (type == SDLK_UP) // move forward if no wall
//{	printf("%scale\n", type);
//if (worldMap[(Uint32)(env->cam.posX + env->directionX *env->cam.move_speed)][(Uint32)(env->cam.posY)] == false)
//env->cam.posX += env->directionX *env->cam.move_speed;
//if (worldMap[(Uint32)(env->cam.posX)][(Uint32)(env->cam.posY + env->dirY *env->cam.move_speed)] == false)
//env->cam.posY += env->dirY *env->cam.move_speed;
//}
//if (type == SDLK_DOWN) //move backwards if no wall
//{
//if (worldMap[(Uint32)(env->cam.posX - env->directionX *env->cam.move_speed)][(Uint32)(env->cam.posY)] == false)
//env->cam.posX -= env->directionX *env->cam.move_speed;
//if (worldMap[(Uint32)env->cam.posX][(Uint32)(env->cam.posY - env->dirY *env->cam.move_speed)] == false)
//env->cam.posY -= env->dirY *env->cam.move_speed;
//}
//
//if (type == SDLK_RIGHT) //rotate to the right
//{	//both camera dir and camera plane must be rotated
//double oldDirX = env->directionX;
//env->directionX = env->directionX * cos(-env->cam.rotate_speed) - env->dirY * sin
//		(-env->cam.rotate_speed);
//env->dirY = oldDirX * sin(-env->cam.rotate_speed) + env->dirY * cos
//		(-env->cam.rotate_speed);
//double oldplane.x = env->cam.plane.x;
//env->cam.plane.x = env->cam.plane.x * cos(-env->cam.rotate_speed) - env->cam.plane.y * sin
//		(-env->cam.rotate_speed);
//env->cam.plane.y = oldplane.x * sin(-env->cam.rotate_speed) + env->cam.plane.y * cos
//		(-env->cam.rotate_speed);
//}
//if (type == SDLK_LEFT) //rotate to the left
//{	//both camera dir and camera plane must be rotated
//double oldDirX = env->directionX;
//env->directionX = env->directionX * cos(env->cam.rotate_speed) - env->dirY * sin
//		(env->cam.rotate_speed);
//env->dirY = oldDirX * sin(env->cam.rotate_speed) + env->dirY * cos
//		(env->cam.rotate_speed);
//double oldplane.x = env->cam.plane.x;
//env->cam.plane.x = env->cam.plane.x * cos(env->cam.rotate_speed) - env->cam.plane.y * sin
//		(env->cam.rotate_speed);
//env->cam.plane.y = oldplane.x * sin(env->cam.rotate_speed) + env->cam.plane.y * cos
//		(env->cam.rotate_speed);
//}
//if (env->event.type == SDL_QUIT)
//{
//env->game_over = true;
//}