/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/18 17:13:08 by dromanic          #+#    #+#             */
/*   Updated: 2018/10/17 12:21:13 by dromanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

Uint32		*chose_gen_or_image(t_env *env, Uint32 gen_id, Uint32 img_id)
{
	return ((env->tex_mode == 1) ? env->gen_texture[gen_id]
								 : env->surfaces[img_id]->pixels);
}
static void	frame_rate_adjustment(t_env *env, t_fps *fps)
{
	fps->previous_tick = fps->current_tick;
	fps->current_tick = SDL_GetTicks();
	fps->frame_time = (fps->current_tick - fps->previous_tick) / 1000.f;
	env->cam.move_speed = fps->frame_time * 5; //in squares/second
	env->cam.rotate_speed = fps->frame_time * 3; //in radians/second
	if ((fps->frame_limit_second) > fps->current_tick - fps->previous_tick)
		SDL_Delay(fps->frame_limit_second -
				  (fps->current_tick - fps->previous_tick));
	//prSint32f("%f\n", 1.0 / frame_time); //FPS counter
}

int			main(void)//Uint32 argc, char **argv)
{
	t_env	*env;
	Uint32	worldMap[mapWidth][mapHeight] =
	{
		{8,8,8,8,8,8,8,8,8,8,8,4,4,6,4,4,6,4,6,4,4,4,6,4},
		{8,0,0,0,0,0,0,0,0,0,8,4,0,0,0,0,0,0,0,0,0,0,0,4},
		{8,0,3,3,0,0,0,0,0,8,8,4,0,0,0,0,0,0,0,0,0,0,0,6},
		{8,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6},
		{8,0,3,3,0,0,0,0,0,8,8,4,0,0,0,0,0,0,0,0,0,0,0,4},
		{8,0,0,0,0,0,0,0,0,0,8,4,0,0,0,0,0,6,6,6,0,6,4,6},
		{8,8,8,8,0,8,8,8,8,8,8,4,4,4,4,4,4,6,0,0,0,0,0,6},
		{7,7,7,7,0,7,7,7,7,0,8,0,8,0,8,0,8,4,0,4,0,6,0,6},
		{7,7,0,0,0,0,0,0,7,8,0,8,0,8,0,8,8,6,0,0,0,0,0,6},
		{7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,8,6,0,0,0,0,0,4},
		{7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,8,6,0,6,0,6,0,6},
		{7,7,0,0,0,0,0,0,7,8,0,8,0,8,0,8,8,6,4,6,0,6,6,6},
		{7,7,7,7,0,7,7,7,7,8,8,4,0,6,8,4,8,3,3,3,0,3,3,3},
		{2,2,2,2,0,2,2,2,2,4,6,4,0,0,6,0,6,3,0,0,0,0,0,3},
		{2,2,0,0,0,0,0,2,2,4,0,0,0,0,0,0,4,3,0,0,0,0,0,3},
		{2,0,0,0,0,0,0,0,2,4,0,0,0,0,0,0,4,3,0,0,0,0,0,3},
		{1,0,0,0,0,0,0,0,1,4,4,4,4,4,6,0,6,3,3,0,0,0,3,3},
		{2,0,0,0,0,0,0,0,2,2,2,1,2,2,2,6,6,0,0,5,0,5,0,5},
		{2,2,0,0,0,0,0,2,2,2,0,0,0,2,2,0,5,0,5,0,0,0,5,5},
		{2,0,0,0,0,0,0,0,2,0,0,0,0,0,2,5,0,5,0,5,0,5,0,5},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5},
		{2,0,0,0,0,0,0,0,2,0,0,0,0,0,2,5,0,5,0,5,0,5,0,5},
		{2,2,0,0,0,0,0,2,2,2,0,0,0,2,2,0,5,0,5,0,0,0,5,5},
		{2,2,2,2,1,2,2,2,2,2,2,1,2,2,2,5,5,5,5,5,5,5,5,5}
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
