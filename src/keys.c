/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/22 15:22:29 by dromanic          #+#    #+#             */
/*   Updated: 2018/10/08 18:24:08 by dromanic         ###   ########.fr       */
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
		if (worldMap[(Uint32)(env->posX + env->dirX * env->moveSpeed)]
			[(Uint32)(env->posY)] == false)
			env->posX += env->dirX * env->moveSpeed;
		if (worldMap[(Uint32)(env->posX)]
			[(Uint32)(env->posY + env->dirY * env->moveSpeed)] == false)
			env->posY += env->dirY * env->moveSpeed;
	}
	if (env->state[SDL_SCANCODE_S]) //move backwards if no wall
	{
		if (worldMap[(Uint32)(env->posX - env->dirX * env->moveSpeed)]
			[(Uint32)(env->posY)] == false)
			env->posX -= env->dirX * env->moveSpeed;
		if (worldMap[(Uint32)env->posX]
			[(Uint32)(env->posY - env->dirY * env->moveSpeed)] == false)
			env->posY -= env->dirY * env->moveSpeed;
	}

	if	(env->state[SDL_SCANCODE_A]) // move forward if no wall
	{
		if (worldMap[(Uint32)(env->posX + env->dirY * env->moveSpeed)]
			[(Uint32)(env->posY)] == false)
			env->posX += env->dirY * env->moveSpeed;
		if (worldMap[(Uint32)(env->posX)]
			[(Uint32)(env->posY + env->dirX * env->moveSpeed)] == false)
			env->posY += env->dirX * env->moveSpeed;
	}
	if (env->state[SDL_SCANCODE_D]) //move backwards if no wall
	{
		if (worldMap[(Uint32)(env->posX - env->dirY * env->moveSpeed)]
			[(Uint32)(env->posY)] == false)
			env->posX -= env->dirY * env->moveSpeed;
		if (worldMap[(Uint32)env->posX]
			[(Uint32)(env->posY - env->dirX * env->moveSpeed)] == false)
			env->posY -= env->dirX * env->moveSpeed;
	}


	if (env->state[SDL_SCANCODE_E]) //rotate to the right
	{    //both camera direction and camera plane must be rotated
		float oldDirX = env->dirX;
		env->dirX = env->dirX * cos(-env->rotateSpeed) - env->dirY * sin
				(-env->rotateSpeed);
		env->dirY = oldDirX * sin(-env->rotateSpeed) + env->dirY * cos
				(-env->rotateSpeed);
		float oldPlaneX = env->planeX;
		env->planeX =
				env->planeX * cos(-env->rotateSpeed) - env->planeY * sin
						(-env->rotateSpeed);
		env->planeY =
				oldPlaneX * sin(-env->rotateSpeed) + env->planeY * cos
						(-env->rotateSpeed);
	}
	if (env->state[SDL_SCANCODE_Q]) //rotate to the left
	{    //both camera direction and camera plane must be rotated
		float oldDirX = env->dirX;
		env->dirX      =
				env->dirX * cos(env->rotateSpeed) - env->dirY * sin
						(env->rotateSpeed);
		env->dirY      =
				oldDirX * sin(env->rotateSpeed) + env->dirY * cos
						(env->rotateSpeed);
		float oldPlaneX = env->planeX;
		env->planeX =
				env->planeX * cos(env->rotateSpeed) - env->planeY * sin
						(env->rotateSpeed);
		env->planeY =
				oldPlaneX * sin(env->rotateSpeed) + env->planeY * cos
						(env->rotateSpeed);
	}
}
//if (type == SDLK_UP) // move forward if no wall
//{	printf("%d\n", type);
//if (worldMap[(Uint32)(env->posX + env->dirX * env->moveSpeed)][(Uint32)(env->posY)] == false)
//env->posX += env->dirX * env->moveSpeed;
//if (worldMap[(Uint32)(env->posX)][(Uint32)(env->posY + env->dirY * env->moveSpeed)] == false)
//env->posY += env->dirY * env->moveSpeed;
//}
//if (type == SDLK_DOWN) //move backwards if no wall
//{
//if (worldMap[(Uint32)(env->posX - env->dirX * env->moveSpeed)][(Uint32)(env->posY)] == false)
//env->posX -= env->dirX * env->moveSpeed;
//if (worldMap[(Uint32)env->posX][(Uint32)(env->posY - env->dirY * env->moveSpeed)] == false)
//env->posY -= env->dirY * env->moveSpeed;
//}
//
//if (type == SDLK_RIGHT) //rotate to the right
//{	//both camera direction and camera plane must be rotated
//double oldDirX = env->dirX;
//env->dirX = env->dirX * cos(-env->rotateSpeed) - env->dirY * sin
//		(-env->rotateSpeed);
//env->dirY = oldDirX * sin(-env->rotateSpeed) + env->dirY * cos
//		(-env->rotateSpeed);
//double oldPlaneX = env->planeX;
//env->planeX = env->planeX * cos(-env->rotateSpeed) - env->planeY * sin
//		(-env->rotateSpeed);
//env->planeY = oldPlaneX * sin(-env->rotateSpeed) + env->planeY * cos
//		(-env->rotateSpeed);
//}
//if (type == SDLK_LEFT) //rotate to the left
//{	//both camera direction and camera plane must be rotated
//double oldDirX = env->dirX;
//env->dirX = env->dirX * cos(env->rotateSpeed) - env->dirY * sin
//		(env->rotateSpeed);
//env->dirY = oldDirX * sin(env->rotateSpeed) + env->dirY * cos
//		(env->rotateSpeed);
//double oldPlaneX = env->planeX;
//env->planeX = env->planeX * cos(env->rotateSpeed) - env->planeY * sin
//		(env->rotateSpeed);
//env->planeY = oldPlaneX * sin(env->rotateSpeed) + env->planeY * cos
//		(env->rotateSpeed);
//}
//if (env->event.type == SDL_QUIT)
//{
//env->game_over = true;
//}