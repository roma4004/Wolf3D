/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/22 15:22:29 by dromanic          #+#    #+#             */
/*   Updated: 2018/10/11 17:36:00 by dromanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	event_handler(t_env *env, Sint32 worldMap[mapWidth][mapHeight])
{
	SDL_PumpEvents();
	while (SDL_PollEvent(&env->event) && !env->game_over)
		if (env->event.type == SDL_QUIT && (env->game_over = true))
			break ;
	if (env->state[SDL_SCANCODE_ESCAPE])
		env->game_over = true;
	if (env->state[SDL_SCANCODE_W]) // move forward if no wall
	{
		if (worldMap[(Uint32)(env->pos.x + env->direction.x * env->moveSpeed)]
			[(Uint32)(env->pos.y)] == false)
			env->pos.x += env->direction.x * env->moveSpeed;
		if (worldMap[(Uint32)(env->pos.x)]
			[(Uint32)(env->pos.y + env->direction.y * env->moveSpeed)] == false)
			env->pos.y += env->direction.y * env->moveSpeed;
	}
	if (env->state[SDL_SCANCODE_S]) //move backwards if no wall
	{
		if (worldMap[(Uint32)(env->pos.x - env->direction.x * env->moveSpeed)]
			[(Uint32)(env->pos.y)] == false)
			env->pos.x -= env->direction.x * env->moveSpeed;
		if (worldMap[(Uint32)env->pos.x]
			[(Uint32)(env->pos.y - env->direction.y * env->moveSpeed)] == false)
			env->pos.y -= env->direction.y * env->moveSpeed;
	}

	if	(env->state[SDL_SCANCODE_A]) // move forward if no wall
	{
		if (worldMap[(Uint32)(env->pos.x + env->direction.y * env->moveSpeed)]
			[(Uint32)(env->pos.y)] == false)
			env->pos.x += env->direction.y * env->moveSpeed;
		if (worldMap[(Uint32)(env->pos.x)]
			[(Uint32)(env->pos.y + env->direction.x * env->moveSpeed)] == false)
			env->pos.y += env->direction.x * env->moveSpeed;
	}
	if (env->state[SDL_SCANCODE_D]) //move backwards if no wall
	{
		if (worldMap[(Uint32)(env->pos.x - env->direction.y * env->moveSpeed)]
			[(Uint32)(env->pos.y)] == false)
			env->pos.x -= env->direction.y * env->moveSpeed;
		if (worldMap[(Uint32)env->pos.x]
			[(Uint32)(env->pos.y - env->direction.x * env->moveSpeed)] == false)
			env->pos.y -= env->direction.x * env->moveSpeed;
	}


	if (env->state[SDL_SCANCODE_E]) //rotate to the right
	{    //both camera direction and camera plane must be rotated
		float oldDirX = env->direction.x;
		env->direction.x = env->direction.x * cos(-env->rotateSpeed)
						- env->direction.y * sin(-env->rotateSpeed);
		env->direction.y = oldDirX * sin(-env->rotateSpeed)
						+ env->direction.y * cos(-env->rotateSpeed);
		float oldplanex = env->plane.x;
		env->plane.x = env->plane.x * cos(-env->rotateSpeed)
					- env->plane.y * sin(-env->rotateSpeed);
		env->plane.y =
				oldplanex * sin(-env->rotateSpeed) + env->plane.y * cos
						(-env->rotateSpeed);
	}
	if (env->state[SDL_SCANCODE_Q]) //rotate to the left
	{    //both camera direction and camera plane must be rotated
		double oldDirX = env->direction.x;
		env->direction.x = env->direction.x * cos(env->rotateSpeed)
						- env->direction.y * sin(env->rotateSpeed);
		env->direction.y = oldDirX * sin(env->rotateSpeed)
				+ env->direction.y * cos(env->rotateSpeed);
		double oldplanex = env->plane.x;
		env->plane.x = env->plane.x * cos(env->rotateSpeed)
					- env->plane.y * sin(env->rotateSpeed);
		env->plane.y = oldplanex * sin(env->rotateSpeed)
					+ env->plane.y * cos(env->rotateSpeed);
	}
}
//if (type == SDLK_UP) // move forward if no wall
//{	printf("%d\n", type);
//if (worldMap[(Uint32)(env->posX + env->directionX * env->moveSpeed)][(Uint32)(env->posY)] == false)
//env->posX += env->directionX * env->moveSpeed;
//if (worldMap[(Uint32)(env->posX)][(Uint32)(env->posY + env->dirY * env->moveSpeed)] == false)
//env->posY += env->dirY * env->moveSpeed;
//}
//if (type == SDLK_DOWN) //move backwards if no wall
//{
//if (worldMap[(Uint32)(env->posX - env->directionX * env->moveSpeed)][(Uint32)(env->posY)] == false)
//env->posX -= env->directionX * env->moveSpeed;
//if (worldMap[(Uint32)env->posX][(Uint32)(env->posY - env->dirY * env->moveSpeed)] == false)
//env->posY -= env->dirY * env->moveSpeed;
//}
//
//if (type == SDLK_RIGHT) //rotate to the right
//{	//both camera direction and camera plane must be rotated
//double oldDirX = env->directionX;
//env->directionX = env->directionX * cos(-env->rotateSpeed) - env->dirY * sin
//		(-env->rotateSpeed);
//env->dirY = oldDirX * sin(-env->rotateSpeed) + env->dirY * cos
//		(-env->rotateSpeed);
//double oldplane.x = env->plane.x;
//env->plane.x = env->plane.x * cos(-env->rotateSpeed) - env->plane.y * sin
//		(-env->rotateSpeed);
//env->plane.y = oldplane.x * sin(-env->rotateSpeed) + env->plane.y * cos
//		(-env->rotateSpeed);
//}
//if (type == SDLK_LEFT) //rotate to the left
//{	//both camera direction and camera plane must be rotated
//double oldDirX = env->directionX;
//env->directionX = env->directionX * cos(env->rotateSpeed) - env->dirY * sin
//		(env->rotateSpeed);
//env->dirY = oldDirX * sin(env->rotateSpeed) + env->dirY * cos
//		(env->rotateSpeed);
//double oldplane.x = env->plane.x;
//env->plane.x = env->plane.x * cos(env->rotateSpeed) - env->plane.y * sin
//		(env->rotateSpeed);
//env->plane.y = oldplane.x * sin(env->rotateSpeed) + env->plane.y * cos
//		(env->rotateSpeed);
//}
//if (env->event.type == SDL_QUIT)
//{
//env->game_over = true;
//}