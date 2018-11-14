/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/21 20:43:55 by dromanic          #+#    #+#             */
/*   Updated: 2018/10/23 19:14:43 by dromanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void		set_texture_pixel(t_env *env, t_ray *ray,
									t_line *line, t_flags *flags)
{
	if (flags->is_compass_texture)
	{
		line->tex_num = line->side;
		if (line->side == 0 && ray->dir.x > 0)
			line->tex_num += 1;
		else if (line->side == 0 && ray->dir.x < 0)
			line->tex_num += 2;
		else if (line->side == 1 && ray->dir.y > 0)
			line->tex_num += 3;
		else if (line->side == 1 && ray->dir.y < 0)
			line->tex_num += 4;
		line->tex_num %= TEXTURES;
	}
	while (++line->start_y < line->end_y)
	{
		line->img = flags->mode == 1 ? env->gen_tex[line->tex_num]
									: env->img_tex[line->tex_num]->pixels;
		line->scale = line->start_y * 256 - env->win_height_x128
									+ (Uint32)line->height * 128;
		line->tex_y = line->scale * TEX_HEIGHT / (Uint32)line->height / 256;
		line->color = line->img[TEX_HEIGHT * line->tex_y + line->texture.x];
		(line->side) ? line->color = (line->color >> 1) & 8355711 : 0;
		env->buff[line->start_y][line->x] = line->color;
	}
}

static void		painting(t_env *env, t_ray *ray, t_line *line, Uint32 **map)
{
	if (env->flags.mode)
	{
		line->tex_num = map[ray->pos.x][ray->pos.y] - 1;
		ray->wall_x = (line->side == 0) ? env->cam.pos.y + line->normal
					* ray->dir.y : env->cam.pos.x + line->normal * ray->dir.x;
		ray->wall_x -= floor(ray->wall_x);
		line->texture.x = (Uint32)(ray->wall_x * TEX_WIDTH);
		if ((!line->side && ray->dir.x > 0) || (line->side && ray->dir.y < 0))
			line->texture.x = TEX_WIDTH - line->texture.x - 1;
		while (++line->start_y < line->end_y)
			set_texture_pixel(env, ray, line, &env->flags);
	}
	else
		while (line->start_y < line->end_y)
			env->buff[line->start_y++][line->x] =
				chose_color(map[ray->pos.x][ray->pos.y], (bool)line->side);
}

static void		draw_wall_line(t_env *env, Uint32 **map,
								t_ray *ray, t_line *line)
{
	t_cam	*cam;

	cam = &env->cam;
	while (1)
	{
		ray->x_less = ray->dist.x < ray->dist.y;
		ray->x_less ? ray->dist.x += ray->step.x : (ray->dist.y += ray->step.y);
		ray->x_less ? ray->pos.x += cam->step.x : (ray->pos.y += cam->step.y);
		line->side = ray->x_less ? 0 : 1;
		if (map[ray->pos.x][ray->pos.y] > 0)
			break ;
	}
	line->normal = (!line->side)
		? (ray->pos.x - cam->pos.x + ((1 - cam->step.x) >> 1)) / ray->dir.x
		: (ray->pos.y - cam->pos.y + ((1 - cam->step.y) >> 1)) / ray->dir.y;
	line->height = WIN_HEIGHT / line->normal;
	line->half = (Uint32)line->height >> 1;
	line->start_y = (Uint32)((-line->half + cam->center.y <= 0)
		? 0 : -line->half + cam->center.y);
	line->end_y = (Uint32)((line->half + cam->center.y) >= WIN_HEIGHT
		? WIN_HEIGHT - 1 : line->half + cam->center.y);
	line->x = (Uint32)ray->x;
	painting(env, ray, line, map);
}

static void		draw_floor_celling_line(t_env *env, t_ray *ray,
										t_line *line, t_flags *fl)
{
	line->start.x = ray->pos.x + ((!line->side && ray->dir.x < 0) ? 1 : 0);
	line->start.y = ray->pos.y + ((line->side && ray->dir.y < 0) ? 1 : 0);
	(!line->side && ray->dir.x != 0) ? line->start.y += ray->wall_x : 0;
	(line->side && ray->dir.y != 0) ? line->start.x += ray->wall_x : 0;
	line->start_y = line->end_y;
	while (++line->start_y < WIN_HEIGHT)
	{
		line->current_dist = WIN_HEIGHT / (2.0 * line->start_y - WIN_HEIGHT);
		line->weight = line->current_dist / line->normal;
		line->coords.x = line->weight * line->start.x
			+ (1 - line->weight) * env->cam.pos.x;
		line->coords.y = line->weight * line->start.y
			+ (1 - line->weight) * env->cam.pos.y;
		line->texture.x = (int)(line->coords.x * TEX_WIDTH) % TEX_WIDTH;
		line->texture.y = (int)(line->coords.y * TEX_HEIGHT) % TEX_HEIGHT;
		line->img = fl->mode == 2 ? env->img_tex[6]->pixels : env->gen_tex[3];
		env->buff[line->start_y][(Uint32)ray->x] = fl->mode == 0 ? 0x424242
			: (line->img[TEX_WIDTH * line->texture.y + line->texture.x] >> 1)
				& 8355711;
		line->img = fl->mode == 2 ? env->img_tex[3]->pixels : env->gen_tex[6];
		env->buff[WIN_HEIGHT - line->start_y][(Uint32)ray->x] =
			fl->mode == 0 ? 0x7e00ff :
				line->img[TEX_WIDTH * line->texture.y + line->texture.x];
	}
}

void			raycasting(t_env *env, Uint32 **map)
{
	t_ray	ray;
	t_line	line;
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
		draw_wall_line(env, map, &ray, &line);
		draw_floor_celling_line(env, &ray, &line, &env->flags);
	}
}
