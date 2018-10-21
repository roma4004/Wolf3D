/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interface.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/24 14:48:59 by dromanic          #+#    #+#             */
/*   Updated: 2018/10/21 13:56:00 by dromanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int		render_interface(t_env *env, t_txt *txt)
{
//Sint32 messageTextLength = snprintf(NULL, 0, "FPS: %d",env->fps.value);
	//char *messageText = (char *)malloc(8 + 1);
	//snprintf(env->fps.messageText, 8 + 1, "FPS: %d", env->fps.value);
	txt->sur_str = TTF_RenderUTF8_Blended(txt->font, "FPS: ", txt->color);
	txt->tex_str = SDL_CreateTextureFromSurface(env->renderer, txt->sur_str);
	if (TTF_SizeUTF8(txt->font, "FPS: ",
			&txt->width, &txt->height) == -1) {
		printf("%s\n", SDL_GetError());
		SDL_Quit();
		return 1;
	}
	txt->rect_txt.x = 10;
	txt->rect_txt.y = 10;
	txt->rect_txt.w = txt->width;
	txt->rect_txt.h = txt->height;
	SDL_RenderCopy(env->renderer, txt->tex_str, NULL, &txt->rect_txt);

	txt->val[0] = (u_char)((env->fps.value / 10 % 10) + '0');
	txt->val[1] = (u_char)((env->fps.value % 10) + '0');
	txt->val[2] = '\0';

	txt->sur_val = TTF_RenderUTF8_Blended(txt->font, txt->val,
								txt->color);
	txt->tex_val = SDL_CreateTextureFromSurface(env->renderer, txt->sur_val);
	if (TTF_SizeUTF8(txt->font, txt->val,
			&txt->width, &txt->height) == -1) {
		printf("%s\n", SDL_GetError());
		SDL_Quit();
		return 1;
	}
	txt->rect_val.x = txt->rect_txt.x + 60;
	txt->rect_val.y = txt->rect_txt.y;
	txt->rect_val.w = txt->width;
	txt->rect_val.h = txt->height;
	SDL_RenderCopy(env->renderer, txt->tex_val, NULL, &env->txt.rect_val);


	SDL_DestroyTexture(txt->tex_str);
	SDL_FreeSurface(txt->sur_str);
	SDL_DestroyTexture(txt->tex_val);
	SDL_FreeSurface(txt->sur_val);
	return (0);
}