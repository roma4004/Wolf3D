/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/21 20:43:55 by dromanic          #+#    #+#             */
/*   Updated: 2018/10/14 20:03:35 by dromanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void		clear_img_buff(t_env *env)
{
	Sint32	y;
	Sint32	x;

	if (!env)
		return ;
	y = -1;
	while (++y < WIN_HEIGHT)
	{
		x = -1;
		while (++x < WIN_WIDTH)
			env->img_buff[y][x] = 0x0;
	}
}

void		frame_limit(Uint32 current_tick, Uint32 previous_tick,
						Uint32 frame_limit_second)
{
	if ((frame_limit_second) > current_tick - previous_tick)
		SDL_Delay(frame_limit_second - (current_tick - previous_tick));
}

void		painting(t_env *env, t_ray *ray, t_line *line,
					Uint32 worldMap[mapWidth][mapHeight])
{
	if (env->texture_mode)
	{
		line->tex_num = worldMap[ray->pos.x][ray->pos.y] - 1;
		ray->wall_x = (line->side == 0) ? env->pos.y + line->normal * ray->dir.y
									: env->pos.x + line->normal * ray->dir.x;
		ray->wall_x -= floor(ray->wall_x);
		line->tex_x = (Uint32)(ray->wall_x * tex_width);//x coordinate on the texture
		if ((!line->side && ray->dir.x > 0) || (line->side && ray->dir.y < 0))
			line->tex_x = tex_width - line->tex_x - 1;
		while (++line->start_y < line->end_y)
		{
			line->img = (env->texture_mode == 1) ? env->texture[line->tex_num]
										: env->surfaces[line->tex_num]->pixels;
			line->d = line->start_y * 256 - WIN_HEIGHT * 128 +
						(Uint32)line->height * 128;//TODO: avoid the division to speed this up
			line->tex_y  = (Sint32)(line->d * tex_height / line->height / 256);
			line->color = line->img[tex_height * line->tex_y + line->tex_x];
			(line->side) ? line->color = (line->color >> 1) & 8355711 : 0;
			env->img_buff[(Sint32)line->start_y][(Sint32)line->x] = line->color;
		}
	}
	else
		while (line->start_y < line->end_y)
			env->img_buff[(Sint32)line->start_y++][(Sint32)line->x] =
				chose_color(worldMap[ray->pos.x][ray->pos.y], line->side);
}

static void	draw_line(t_env *env, Uint32 worldMap[mapWidth][mapHeight],
		t_ray *ray)
{
	t_line	line;

	while (1)
	{
		ray->x_less = ray->dist.x < ray->dist.y;
		ray->x_less ? ray->dist.x += ray->step.x : (ray->dist.y += ray->step.y);
		ray->x_less ? ray->pos.x += env->step.x : (ray->pos.y += env->step.y);
		line.side = ray->x_less ? false : true;
		if (worldMap[ray->pos.x][ray->pos.y] > 0)
			break;
	}
	line.normal = (!line.side)
			? (ray->pos.x - env->pos.x + (1 - env->step.x) / 2) / ray->dir.x
			: (ray->pos.y - env->pos.y + (1 - env->step.y) / 2) / ray->dir.y;
	line.height = WIN_HEIGHT / line.normal * env->wall_scale;
	line.start_y = -line.height / 2 + env->win_center.y;
	if (line.start_y < 0)
		line.start_y = 0;
	line.end_y = line.height / 2 + env->win_center.y;
	if (line.end_y >= WIN_HEIGHT)
		line.end_y = WIN_HEIGHT - 1;
	line.x = (Uint32)ray->x;
	painting(env, ray, &line, worldMap);
}

void		raycasting(t_env *env, Uint32 worldMap[mapWidth][mapHeight])
{
	t_ray	ray;

	ray.x = 0;
	while (++ray.x < WIN_WIDTH)
	{
		env->camera_x = 2 * ray.x / WIN_WIDTH - 1;
		ray.dir.x = env->cam_dir.x * env->zoom + env->plane.x * env->camera_x;
		ray.dir.y = env->cam_dir.y * env->zoom + env->plane.y * env->camera_x;
		ray.pos.x = (Uint32)env->pos.x;
		ray.pos.y = (Uint32)env->pos.y;
		ray.step.x = fabs(1 / ray.dir.x);
		ray.step.y = fabs(1 / ray.dir.y);
		env->step.x = ray.dir.x < 0 ? -1 : 1;
		env->step.y = ray.dir.y < 0 ? -1 : 1;
		ray.dist.x = ray.step.x * (ray.dir.x < 0
				? env->pos.x - ray.pos.x : ray.pos.x + 1 - env->pos.x);
		ray.dist.y = ray.step.y * (ray.dir.y < 0
				? env->pos.y - ray.pos.y : ray.pos.y + 1 - env->pos.y);
		draw_line(env, worldMap, &ray);
	}
}

void		get_time_ticks(t_fps *fps)
{
	fps->previous_tick = fps->current_tick;
	fps->current_tick = SDL_GetTicks();
	fps->frame_time = (fps->current_tick - fps->previous_tick) / 1000.f;
	//prSint32f("%f\n", 1.0 / frame_time); //FPS counter
}
