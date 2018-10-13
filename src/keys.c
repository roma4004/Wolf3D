/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/22 15:22:29 by dromanic          #+#    #+#             */
/*   Updated: 2018/10/12 17:52:32 by dromanic         ###   ########.fr       */
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
		if (worldMap[(Uint32)(env->pos.x + env->player_dir.x * env->moveSpeed)]
			[(Uint32)(env->pos.y)] == false)
			env->pos.x += env->player_dir.x * env->moveSpeed;
		if (worldMap[(Uint32)(env->pos.x)]
			[(Uint32)(env->pos.y + env->player_dir.y * env->moveSpeed)] == false)
			env->pos.y += env->player_dir.y * env->moveSpeed;
	}
	if (env->state[SDL_SCANCODE_S]) //move backwards if no wall
	{
		if (worldMap[(Uint32)(env->pos.x - env->player_dir.x * env->moveSpeed)]
			[(Uint32)(env->pos.y)] == false)
			env->pos.x -= env->player_dir.x * env->moveSpeed;
		if (worldMap[(Uint32)env->pos.x]
			[(Uint32)(env->pos.y - env->player_dir.y * env->moveSpeed)] == false)
			env->pos.y -= env->player_dir.y * env->moveSpeed;
	}

	if	(env->state[SDL_SCANCODE_A]) // move forward if no wall
	{//both camera dir and camera plane must be rotated
//		double oldDirX = env->dir.x;
//		env->dir.x = env->dir.x * cos(env->rotateSpeed) - env->dir.y * sin(env->rotateSpeed);
//		env->dir.y = oldDirX * sin(env->rotateSpeed) + env->dir.y * cos(env->rotateSpeed);
//		double oldPlaneX = env->plane.x;
//		env->plane.x = env->plane.x * cos(env->rotateSpeed) - env->plane.y * sin(env->rotateSpeed);
//		env->plane.y = oldPlaneX * sin(env->rotateSpeed) + env->plane.y * cos(env->rotateSpeed);

		if (worldMap[(Uint32)(env->pos.x + env->player_dir.y * env->moveSpeed)]
			[(Uint32)(env->pos.y)] == false)
			env->pos.x += env->player_dir.y * env->moveSpeed;
		if (worldMap[(Uint32)(env->pos.x)]
			[(Uint32)(env->pos.y + env->player_dir.x * env->moveSpeed)] == false)
			env->pos.y += env->player_dir.x * env->moveSpeed;
	}
	if (env->state[SDL_SCANCODE_D]) //move backwards if no wall
	{
		if (worldMap[(Uint32)(env->pos.x - env->player_dir.y * env->moveSpeed)]
			[(Uint32)(env->pos.y)] == false)
			env->pos.x -= env->player_dir.y * env->moveSpeed;
		if (worldMap[(Uint32)env->pos.x]
			[(Uint32)(env->pos.y - env->player_dir.x * env->moveSpeed)] == false)
			env->pos.y -= env->player_dir.x * env->moveSpeed;
	}


	if (env->state[SDL_SCANCODE_E]) //rotate to the right
	{    //both camera dir and camera plane must be rotated
		float oldDirX = env->player_dir.x;
		env->player_dir.x = env->player_dir.x * cos(-env->rotateSpeed)
						- env->player_dir.y * sin(-env->rotateSpeed);
		env->player_dir.y = oldDirX * sin(-env->rotateSpeed)
						+ env->player_dir.y * cos(-env->rotateSpeed);
		float oldplanex = env->plane.x;
		env->plane.x = env->plane.x * cos(-env->rotateSpeed)
					- env->plane.y * sin(-env->rotateSpeed);
		env->plane.y =
				oldplanex * sin(-env->rotateSpeed) + env->plane.y * cos
						(-env->rotateSpeed);
	}
	if (env->state[SDL_SCANCODE_Q]) //rotate to the left
	{    //both camera dir and camera plane must be rotated
		double oldDirX = env->player_dir.x;
		env->player_dir.x = env->player_dir.x * cos(env->rotateSpeed)
						- env->player_dir.y * sin(env->rotateSpeed);
		env->player_dir.y = oldDirX * sin(env->rotateSpeed)
				+ env->player_dir.y * cos(env->rotateSpeed);
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
//{	//both camera dir and camera plane must be rotated
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
//{	//both camera dir and camera plane must be rotated
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