/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interface.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/24 14:48:59 by dromanic          #+#    #+#             */
/*   Updated: 2018/10/24 17:23:03 by dromanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

int			render_interface(t_env *env, t_fps *fps, t_txt *txt)
{
	txt->sur_str = TTF_RenderUTF8_Blended(txt->font, "FPS: ", txt->color);
	txt->tex_str = SDL_CreateTextureFromSurface(env->renderer, txt->sur_str);
	SDL_FreeSurface(txt->sur_str);
	TTF_SizeUTF8(txt->font, "FPS: ", &txt->width, &txt->height);
	txt->rect_txt.x = 10;
	txt->rect_txt.y = 10;
	txt->rect_txt.w = txt->width;
	txt->rect_txt.h = txt->height;
	SDL_RenderCopy(env->renderer, txt->tex_str, NULL, &txt->rect_txt);
	SDL_DestroyTexture(txt->tex_str);
	txt->str[0] = (u_char)(fps->value / 10 % 10 + '0');
	txt->str[1] = (u_char)(fps->value % 10 + '0');
	txt->str[2] = '\0';
	txt->sur_str = TTF_RenderUTF8_Blended(txt->font, txt->str, txt->color);
	txt->tex_str = SDL_CreateTextureFromSurface(env->renderer, txt->sur_str);
	SDL_FreeSurface(txt->sur_str);
	TTF_SizeUTF8(txt->font, txt->str, &txt->width, &txt->height);
	txt->rect_val.x = txt->rect_txt.x + 60;
	txt->rect_val.y = txt->rect_txt.y;
	txt->rect_val.w = txt->width;
	txt->rect_val.h = txt->height;
	SDL_RenderCopy(env->renderer, txt->tex_str, NULL, &env->txt.rect_val);
	SDL_DestroyTexture(txt->tex_str);
	SDL_ClearError();
	return (0);
}

void		show_errors(t_env *env)
{
	if (env->err_id == 404)
		ft_putstr_fd("MAP_ERR", 2);
	if (env->err_id == 405)
		ft_putstr_fd("READ_ERR", 2);
	if (env->err_id == 406)
		ft_putstr_fd("MAP_SIZE_ERR", 2);
	if (env->err_id == 407)
		ft_putstr_fd("INVALID_RESOURCE", 2);
	if (env->err_id == 408)
		ft_putstr_fd("NOT_ENOUGH_SPACE", 2);
	if (env->err_id && errno)
		ft_putstr_fd(" - ", 2);
	if (errno)
		ft_putstr_fd(strerror(errno), 2);
	if (env->err_id || errno)
		ft_putstr_fd("\n", 2);
	if (DEBUG)
	{
		if (ft_strcmp(SDL_GetError(), ""))
		{
			ft_putstr("SDL_LAST_ERROR - ");
			ft_putstr(SDL_GetError());
		}
		ft_putchar('\n');
	}
}
