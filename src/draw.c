/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/21 20:43:55 by dromanic          #+#    #+#             */
/*   Updated: 2018/10/15 20:10:55 by dromanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void		clear_img_buff(t_env *env)
{
	Uint32	y;
	Uint32	x;

	if (!env)
		return ;
	y = 0;
	while (y < WIN_HEIGHT)
	{
		x = 0;
		while (x < WIN_WIDTH)
			env->img_buff[y][x++] = 0x0;
		y++;
	}
}


void		painting(t_env *env, t_ray *ray, t_line *line,
					Uint32 worldMap[mapWidth][mapHeight])
{
	if (env->tex_mode)
	{
		line->tex_num = worldMap[ray->pos.x][ray->pos.y] - 1;
		ray->wall_x = (line->side == 0) ? env->cam.pos.y + line->normal
			 * ray->dir.y : env->cam.pos.x + line->normal * ray->dir.x;
		line->tex_x = (Uint32)((ray->wall_x -= floor(ray->wall_x)) * tex_width); //x coordinate on the gen_texture
		if ((!line->side && ray->dir.x > 0) || (line->side && ray->dir.y < 0))
			line->tex_x = tex_width - line->tex_x - 1;
		while (++line->start_y < line->end_y)
		{
			line->img = (env->tex_mode == 1) ? env->gen_texture[line->tex_num]
										: env->surfaces[line->tex_num]->pixels;
			line->scale = line->start_y * 256 - WIN_HEIGHT * 128 +
						(Uint32)line->height * 128;//TODO: avoid the division to speed this up
			line->tex_y = line->scale * tex_height / (Uint32)line->height / 256;
			line->color = line->img[tex_height * line->tex_y + line->tex_x];
			(line->side) ? line->color = (line->color >> 1) & 8355711 : 0;
			env->img_buff[line->start_y][line->x] = line->color;
		}
	}
	else
		while (line->start_y < line->end_y)
			env->img_buff[line->start_y++][line->x] =
				chose_color(worldMap[ray->pos.x][ray->pos.y], line->side);
}

static void	draw_line(t_env *env, Uint32 worldMap[mapWidth][mapHeight],
		t_ray *ray)
{
	t_line	line;
	t_cam	*cam;

	cam = &env->cam;
	while (1)
	{
		ray->x_less = ray->dist.x < ray->dist.y;
		ray->x_less ? ray->dist.x += ray->step.x : (ray->dist.y += ray->step.y);
		ray->x_less ? ray->pos.x += cam->step.x : (ray->pos.y += cam->step.y);
		line.side = ray->x_less ? false : true;
		if (worldMap[ray->pos.x][ray->pos.y] > 0)
			break;
	}
	line.normal = (!line.side)
			? (ray->pos.x - cam->pos.x + (1 - cam->step.x) / 2) / ray->dir.x
			: (ray->pos.y - cam->pos.y + (1 - cam->step.y) / 2) / ray->dir.y;
	line.height = WIN_HEIGHT / line.normal * cam->wall_scale;
	line.start_y = (Uint32)((-line.height / 2 + cam->center.y < 0)
			? 0 : -line.height / 2 + cam->center.y);
	line.end_y = (Uint32)((line.height / 2 + cam->center.y) >= WIN_HEIGHT
			? WIN_HEIGHT - 1 : line.height / 2 + cam->center.y);
	line.x = (Uint32)ray->x;
	painting(env, ray, &line, worldMap);
}

void		raycasting(t_env *env, Uint32 worldMap[mapWidth][mapHeight])
{
	t_ray	ray;
	t_cam	*cam;

	cam = &env->cam;
	ray.x = 0;
	while (++ray.x < WIN_WIDTH)
	{
		env->cam.x = 2 * ray.x / WIN_WIDTH - 1;
		ray.dir.x = env->cam.dir.x * cam->zoom + cam->plane.x * cam->x;
		ray.dir.y = env->cam.dir.y * cam->zoom + cam->plane.y * cam->x;
		ray.pos.x = (Uint32)cam->pos.x;
		ray.pos.y = (Uint32)cam->pos.y;
		ray.step.x = fabs(1 / ray.dir.x);
		ray.step.y = fabs(1 / ray.dir.y);
		cam->step.x = ray.dir.x < 0 ? -1 : 1;
		cam->step.y = ray.dir.y < 0 ? -1 : 1;
		ray.dist.x = ray.step.x * (ray.dir.x < 0
				? cam->pos.x - ray.pos.x : ray.pos.x + 1 - cam->pos.x);
		ray.dist.y = ray.step.y * (ray.dir.y < 0
				? cam->pos.y - ray.pos.y : ray.pos.y + 1 - cam->pos.y);
		draw_line(env, worldMap, &ray);
	}
}

void		frame_rate_adjustment(t_env *env, t_fps *fps)
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
