/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/18 17:13:08 by dromanic          #+#    #+#             */
/*   Updated: 2018/10/09 16:02:02 by dromanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"


int main(void)//Sint32 argc, char **argv)
{
	t_env	*env;
	float	x;
	Sint32	worldMap[mapWidth][mapHeight] =
	{
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
		{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
		{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
	};

	env = init_env();

	env->posX = 22;
	env->posY = 12;
	env->dirX = -1;
	env->dirY = 0; //initial direction vector
	env->planeX = 0,
	env->planeY = 0.66; //the 2d raycaster version of camera plane
	env->current_tick    = 0; //current_tick of current frame
	env->previous_tick = 0; //current_tick of previous frame

	while (!env->game_over)
	{
//		SDL_SetRenderDrawColor(env->renderer, 255, 0, 0, 255);
//		SDL_RenderClear(env->renderer);
		clear_img_buff(env);
		//ft_bzero(env->img_buff, WIN_WIDTH*WIN_HEIGHT*sizeof(Sint32));
		//
		//
		//ft_memset(env->img_buff, 0x0, WIN_HEIGHT * WIN_WIDTH * sizeof(int));
		x = -1;
		while (++x < WIN_WIDTH)
		{	//calculate ray position and direction
			env->cameraX = 2 * x / WIN_WIDTH - 1; //x-coordinate in camera
			// space
			env->rayDirX = env->dirX + env->planeX * env->cameraX;
			env->rayDirY = env->dirY + env->planeY * env->cameraX;
			//which box of the map we're in
			env->mapX = (Sint32)env->posX;
			env->mapY = (Sint32)env->posY;
			//length of ray from current position to next x or y-side

			//length of ray from one x or y-side to next x or y-side
			env->deltaDistX = fabs(1.0f / env->rayDirX);
			env->deltaDistY = fabs(1.0f / env->rayDirY);
			//what direction to step in x or y-direction (either +1 or -1)

			Sint32 hit = 0; //was there a wall hit?
			//calculate step and initial sideDist
			env->stepX = (Sint32)((env->rayDirX < 0.0f) ? -1 : 1);
			env->stepY = (Sint32)((env->rayDirY < 0.0f) ? -1 : 1);
			env->sideDistX = env->deltaDistX *
					((env->rayDirX < 0.0f) ? (env->posX - env->mapX)
											: (env->mapX + 1 - env->posX));
			env->sideDistY = env->deltaDistY *
					((env->rayDirY < 0.0f) ? (env->posY - env->mapY)
											: (env->mapY + 1 - env->posY));
			while (hit == 0)//perform DDA
			{//jump to next map square, OR in x-direction, OR in y-direction
				if (env->sideDistX < env->sideDistY)
				{
					env->sideDistX += env->deltaDistX;
					env->mapX += env->stepX;
					env->side = 0;
				}
				else
				{
					env->sideDistY += env->deltaDistY;
					env->mapY += env->stepY;
					env->side = 1;
				}
				//Check if ray has hit a wall
				if (worldMap[env->mapX][env->mapY] > 0)
					hit = 1;
			}//Calculate distance projected on camera direction
			// (Euclidean distance will give fisheye effect!)
			if (env->side == 0)
				env->perpWallDist =
						(env->mapX - env->posX + (1.0f - env->stepX) / 2.0f)
							/ env->rayDirX;
			else
				env->perpWallDist =
						(env->mapY - env->posY + (1.0f - env->stepY) / 2.0f)
							/ env->rayDirY;
			//Calculate height of line to draw on screen
			float lineHeight = (float)(WIN_HEIGHT / env->perpWallDist);
			//calculate lowest and highest pixel to fill in current stripe
			float drawStart = -lineHeight / 2.0f + WIN_HEIGHT / 2.0f;
			if (drawStart < 0)
				drawStart = 0;
			float drawEnd = lineHeight / 2.0f + WIN_HEIGHT / 2.0f;
			if (drawEnd >= WIN_HEIGHT)
				drawEnd = WIN_HEIGHT - 1;
			//draw the pixels of the stripe as a vertical line
			while(drawStart < drawEnd)
			{
				env->img_buff[(Sint32)drawStart][(Sint32)x] =
						chose_color(worldMap[env->mapX][env->mapY], env->side);
				drawStart++;
			}
		}
		env->previous_tick = env->current_tick; // timing for input and FPS counter
		env->current_tick = SDL_GetTicks();
		//frameTime is the current_tick this frame has taken, in seconds
		env->frameTime = (env->current_tick - env->previous_tick) / 1000.0f;
		//prSint32f("%f\n", 1.0 / frameTime); //FPS counter
	//	stroboscope_effect when display black_screen before every frame
	//	SDL_RenderPresent(env->renderer);

		//SDL_DestroyTexture(env->texture);
		env->texture =
			SDL_CreateTexture(env->renderer,
				SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_TARGET,
					WIN_WIDTH, WIN_HEIGHT);
		SDL_UpdateTexture(env->texture, NULL, env->img_buff, (WIN_WIDTH << 2));//WIN_WIDTH * sizeof(Sint32));
		SDL_RenderCopy(env->renderer, env->texture, NULL, NULL);
		SDL_RenderPresent(env->renderer);

		//speed modifiers
		env->moveSpeed = env->frameTime * 5.0f; //in squares/second
		env->rotateSpeed = env->frameTime * 3.0f; //in radians/second
		event_handler(env, worldMap);
		frame_limit(env->current_tick, env->previous_tick);
	}


//----------------------------------------------
/*
t_env *env = init_env();
	SDL_Rect player_RECT;
	player_RECT.x = 0;   //Смещение полотна по Х
	player_RECT.y = 0;   //Смещение полотна по Y
	player_RECT.w = 333; //Ширина полотна
	player_RECT.h = 227; //Высота полотна

	SDL_Rect background_RECT;
	background_RECT.x = 0;
	background_RECT.y = 0;
	background_RECT.w = env->display_param.w;
	background_RECT.h = env->display_param.h;

	t_txt	txt;

	txt.messageColor = (SDL_Color){255, 255, 255, 0};
	txt.messageWidth = 0;
	txt.messageHeight = 0;


	Sint32		*canvas = malloc(sizeof(Sint32) * WIN_WIDTH * WIN_HEIGHT);
	//display_Sint32erface(env);
	TTF_Font	*messageFont = TTF_OpenFont(DEF_FONT, 24);

	if (messageFont == NULL) {
		prSint32f("%s\n", SDL_GetError());
		SDL_Quit();
		return 1;
	}
	env->game_over = 0;
	ft_memset(env->framesTimes, 0, sizeof(env->framesTimes));
	env->frameCount = 0;
	env->frameTimeLast = SDL_GetTicks();
	while (!env->game_over)
	{
		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
				env->game_over = true;
		}
		SDL_RenderClear(env->renderer);
		ft_memset(canvas, 128, env->screen_size * sizeof(Sint32));
		for (Sint32 i = 0; i < env->screen_size; i += rand() % 2) {
			canvas[i] = rand();
		}
		SDL_UpdateTexture(env->mainTexture, NULL, canvas,
				WIN_WIDTH * sizeof(Sint32));
		SDL_RenderCopy(env->renderer, env->mainTexture, NULL, NULL);
		{
			env->framesTimesindex = env->frameCount % FRAME_LIMIT;
			env->getticks = SDL_GetTicks();
			env->framesTimes[env->framesTimesindex] =
					env->getticks - env->frameTimeLast;
			env->frameTimeLast = env->getticks;
			env->frameCount++;
			Sint32 count = env->frameCount < FRAME_LIMIT ?
							env->frameCount : FRAME_LIMIT;
			env->fps = 0;
			for (Sint32 i = 0; i < count; i++)
				env->fps += env->framesTimes[i];
			env->fps = 1000.f / (env->fps / count);
			Sint32 messageTextLength = snprSint32f(NULL, 0, "FPS: %f", env->fps);
			char *messageText = (char *) malloc(messageTextLength + 1);
			snprSint32f(messageText, messageTextLength + 1, "FPS: %f", env->fps);
			SDL_Surface *messageSurface =
					TTF_RenderUTF8_Blended(messageFont, messageText,
							txt.messageColor);
			if (messageSurface == NULL) {
				prSint32f("%s\n", SDL_GetError());
				SDL_Quit();
				return 1;
			}
			SDL_Texture *messageTexture =
					SDL_CreateTextureFromSurface(env->renderer, messageSurface);
			if (messageTexture == NULL) {
				prSint32f("%s\n", SDL_GetError());
				SDL_Quit();
				return 1;
			}
			if (TTF_SizeUTF8(messageFont, messageText, &txt.messageWidth,
					&txt.messageHeight) == -1) {
				prSint32f("%s\n", SDL_GetError());
				SDL_Quit();
				return 1;
			}
			txt.rect.x = 10;
			txt.rect.y = 10;
			txt.rect.w = txt.messageWidth;
			txt.rect.h = txt.messageHeight;
			SDL_RenderCopy(env->renderer, messageTexture, NULL, &txt.rect);
			SDL_DestroyTexture(messageTexture);
			SDL_FreeSurface(messageSurface);
			free(messageText);
		}
		SDL_RenderPresent(env->renderer);
	}
	free(canvas);
*/
	/* Select the color for drawing. It is set to red here. */
//	SDL_SetRenderDrawColor(env->renderer, 255, 0, 0, 255);

	/* Clear the entire screen to our selected color. */
//	SDL_RenderClear(env->renderer);

	/* Up until now everything was drawn behind the scenes.
	   This will show the new, red contents of the window. */
//	SDL_RenderPresent(env->renderer);


	//	free_win(env);
	/* Always be sure to clean up */
	SDL_Quit();
	return (0);
}
