/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/18 17:13:08 by dromanic          #+#    #+#             */
/*   Updated: 2018/10/15 19:19:35 by dromanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int main(void)//Uint32 argc, char **argv)
{
	t_env	*env;
	Uint32	worldMap[mapWidth][mapHeight] =
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
	while (!env->game_over)
	{
		frame_rate_adjustment(env, &env->fps);
		clear_img_buff(env);
		raycasting(env, worldMap);
		SDL_UpdateTexture(env->screen, NULL, env->img_buff, (WIN_WIDTH << 2));
		SDL_RenderCopy(env->renderer, env->screen, NULL, NULL);
		SDL_RenderPresent(env->renderer);
		event_handler(env, worldMap);
	}
//----------------------------------------------
/*
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
	//display_interface(env);
	while (!env->game_over)
	{
		SDL_UpdateTexture(env->screen, NULL, env->screen, WIN_WIDTH * sizeof
		(Sint32));
		SDL_RenderCopy(env->renderer, env->screen, NULL, NULL);

			Sint32 messageTextLength = snprintf(NULL, 0, "FPS: %f",
			env->fps.value);
			char *messageText = (char *)malloc(messageTextLength + 1);
			snprintf(messageText, messageTextLength + 1, "FPS: %f", env->fps.value);
			SDL_Surface *messageSurface =
					TTF_RenderUTF8_Blended(env->txt.messageFont, messageText,
							env->txt.color);
			if (messageSurface == NULL) {
				printf("%s\n", SDL_GetError());
				SDL_Quit();
				return 1;
			}
			SDL_Texture *messageTexture =
					SDL_CreateTextureFromSurface(env->renderer, messageSurface);
			if (messageTexture == NULL) {
				printf("%s\n", SDL_GetError());
				SDL_Quit();
				return 1;
			}
			if (TTF_SizeUTF8(env->txt.messageFont, messageText, &env->txt.width,
					&env->txt.height) == -1) {
				printf("%s\n", SDL_GetError());
				SDL_Quit();
				return 1;
			}
			env->txt.rect.x = 10;
			env->txt.rect.y = 10;
			env->txt.rect.w = env->txt.width;
			env->txt.rect.h = env->txt.height;
			SDL_RenderCopy(env->renderer, messageTexture, NULL, &env->txt.rect);
			SDL_DestroyTexture(messageTexture);
			SDL_FreeSurface(messageSurface);
			free(messageText);

		SDL_RenderPresent(env->renderer);
	}
	free(env->screen);
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
