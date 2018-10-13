/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/18 17:13:08 by dromanic          #+#    #+#             */
/*   Updated: 2018/10/13 19:43:58 by dromanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"



int main(void)//Sint32 argc, char **argv)
{
	t_env	*env;
	Sint32	worldMap[mapWidth][mapHeight] =
	{
		{4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,7,7,7,7,7,7,7,7},
		{4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,0,0,0,0,0,0,7},
		{4,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7},
		{4,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7},
		{4,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,7,0,0,0,0,0,0,7},
		{4,0,4,0,0,0,0,5,5,5,5,5,5,5,5,5,7,7,0,7,7,7,7,7},
		{4,0,5,0,0,0,0,5,0,5,0,5,0,5,0,5,7,0,0,0,7,7,7,1},
		{4,0,6,0,0,0,0,5,0,0,0,0,0,0,0,5,7,0,0,0,0,0,0,8},
		{4,0,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,7,7,1},
		{4,0,8,0,0,0,0,5,0,0,0,0,0,0,0,5,7,0,0,0,0,0,0,8},
		{4,0,0,0,0,0,0,5,0,0,0,0,0,0,0,5,7,0,0,0,7,7,7,1},
		{4,0,0,0,0,0,0,5,5,5,5,0,5,5,5,5,7,7,7,7,7,7,7,1},
		{6,6,6,6,6,6,6,6,6,6,6,0,6,6,6,6,6,6,6,6,6,6,6,6},
		{8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
		{6,6,6,6,6,6,0,6,6,6,6,0,6,6,6,6,6,6,6,6,6,6,6,6},
		{4,4,4,4,4,4,0,4,4,4,6,0,6,2,2,2,2,2,2,2,3,3,3,3},
		{4,0,0,0,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,0,0,0,2},
		{4,0,0,0,0,0,0,0,0,0,0,0,6,2,0,0,5,0,0,2,0,0,0,2},
		{4,0,0,0,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,2,0,2,2},
		{4,0,6,0,6,0,0,0,0,4,6,0,0,0,0,0,5,0,0,0,0,0,0,2},
		{4,0,0,5,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,2,0,2,2},
		{4,0,6,0,6,0,0,0,0,4,6,0,6,2,0,0,5,0,0,2,0,0,0,2},
		{4,0,0,0,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,0,0,0,2},
		{4,4,4,4,4,4,4,4,4,4,1,1,1,2,2,2,2,2,2,3,3,3,3,3}
	};
	env = init_env();
	generate_texture(env);
	while (!env->game_over)
	{
		get_time_ticks(&env->fps);
		clear_img_buff(env);
		raycasting(env, worldMap, -1);
		env->main_texture = SDL_CreateTexture(env->renderer,
							SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_TARGET,
							WIN_WIDTH, WIN_HEIGHT);
//		swap_px(env, tex_width * tex_height);
		SDL_UpdateTexture(env->main_texture, NULL, env->img_buff,
							(WIN_WIDTH << 2));//WIN_WIDTH * sizeof(Sint32));
		SDL_RenderCopy(env->renderer, env->main_texture, NULL, NULL);
		SDL_RenderPresent(env->renderer);
		env->moveSpeed = env->fps.frame_time * 5; //in squares/second
		env->rotateSpeed = env->fps.frame_time * 3; //in radians/second
		event_handler(env, worldMap);
		frame_limit(env->fps.current_tick, env->fps.previous_tick,
					env->fps.frame_limit_second);
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
	env->frame_count = 0;
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
		SDL_UpdateTexture(env->main_texture, NULL, canvas,
				WIN_WIDTH * sizeof(Sint32));
		SDL_RenderCopy(env->renderer, env->main_texture, NULL, NULL);
		{
			env->frames_timesindex = env->frame_count % FRAME_LIMIT;
			env->getticks = SDL_GetTicks();
			env->framesTimes[env->frames_timesindex] =
					env->getticks - env->frameTimeLast;
			env->frameTimeLast = env->getticks;
			env->frame_count++;
			Sint32 count = env->frame_count < FRAME_LIMIT ?
							env->frame_count : FRAME_LIMIT;
			env->value = 0;
			for (Sint32 i = 0; i < count; i++)
				env->value += env->framesTimes[i];
			env->value = 1000.f / (env->value / count);
			Sint32 messageTextLength = snprSint32f(NULL, 0, "FPS: %f", env->value);
			char *messageText = (char *) malloc(messageTextLength + 1);
			snprSint32f(messageText, messageTextLength + 1, "FPS: %f", env->value);
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

	quit_program(env);
	return (0);
}
