/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/21 20:43:55 by dromanic          #+#    #+#             */
/*   Updated: 2018/10/18 15:07:40 by dromanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void		set_texture_pixel(t_env *env, t_ray *ray, t_line *line)
{
	if (env->is_compass_texture)
	{
		line->tex_num = line->side;
		if (line->side == 0 && ray->dir.x > 0) line->tex_num += 1;
		else if (line->side == 0 && ray->dir.x < 0) line->tex_num += 2;
		else if (line->side == 1 && ray->dir.y > 0) line->tex_num += 3;
		else if (line->side == 1 && ray->dir.y < 0) line->tex_num += 4;
		line->tex_num %= texture_count;
	}
	while (++line->start_y < line->end_y)
	{
		line->img = chose_gen_or_image (env, line->tex_num, line->tex_num);
		line->scale =
			line->start_y * 256 - WIN_HEIGHT * 128 + (Uint32)line->height * 128;
		line->tex_y = line->scale * tex_height / (Uint32)line->height / 256;
		line->color = line->img[tex_height * line->tex_y + line->texture.x];
		(line->side) ? line->color = (line->color >> 1) & 8355711 : 0;
		env->img_buff[line->start_y][line->x] = line->color;
	}
}

static void		painting(t_env *env, t_ray *ray, t_line *line,
							Uint32 worldMap[mapWidth][mapHeight])
{
	if (env->tex_mode)
	{
		line->tex_num = worldMap[ray->pos.x][ray->pos.y] - 1;
		ray->wall_x = (line->side == 0) ? env->cam.pos.y + line->normal
			 * ray->dir.y : env->cam.pos.x + line->normal * ray->dir.x;
		ray->wall_x -= floor(ray->wall_x);
		line->texture.x = (Uint32)(ray->wall_x * tex_width);
		if ((!line->side && ray->dir.x > 0) || (line->side && ray->dir.y < 0))
			line->texture.x = tex_width - line->texture.x - 1;
		while (++line->start_y < line->end_y)
			set_texture_pixel(env, ray, line);
	}
	else
		while (line->start_y < line->end_y)
			env->img_buff[line->start_y++][line->x] =
				chose_color(worldMap[ray->pos.x][ray->pos.y], line->side);
}

static void		draw_wall_line(t_env *env, Uint32 worldMap[mapWidth][mapHeight],
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
		if (worldMap[ray->pos.x][ray->pos.y] > 0)
			break;
	}
	line->normal = (!line->side)
		? (ray->pos.x - cam->pos.x + ((1 - cam->step.x) >> 1)) / ray->dir.x
		: (ray->pos.y - cam->pos.y + ((1 - cam->step.y) >> 1)) / ray->dir.y;
	line->height = WIN_HEIGHT / line->normal * cam->wall_scale;
	line->half = (Uint32)line->height >> 1;
	line->start_y = (Uint32)((-line->half + cam->center.y <= 0)
		? 0 : -line->half + cam->center.y);
	line->end_y = (Uint32)((line->half + cam->center.y) >= WIN_HEIGHT
		? WIN_HEIGHT - 1 : line->half + cam->center.y);
	line->x = (Uint32)ray->x;
	painting(env, ray, line, worldMap);
}

static void		draw_floor_celling_line(t_env *env, t_ray *ray, t_line *line)
{
	line->floor_wall.x = ray->pos.x + ((!line->side && ray->dir.x < 0) ? 1 : 0);
	line->floor_wall.y = ray->pos.y + ((line->side && ray->dir.y < 0) ? 1 : 0);
	if (!line->side && ray->dir.x != 0)
		line->floor_wall.y += ray->wall_x;
	if (line->side && ray->dir.y != 0)
		line->floor_wall.x += ray->wall_x;
	line->start_y = line->end_y ;
	while (++line->start_y < WIN_HEIGHT)
	{
		line->current_dist = WIN_HEIGHT / (2.0 * line->start_y - WIN_HEIGHT);
		line->weight = line->current_dist / line->normal;
		line->currentFloor.x = line->weight * line->floor_wall.x
			+ (1 / env->cam.wall_scale - line->weight) * env->cam.pos.x;
		line->currentFloor.y = line->weight * line->floor_wall.y
			+ (1 / env->cam.wall_scale - line->weight) * env->cam.pos.y;
		line->texture.x = (int)(line->currentFloor.x * tex_width) % tex_width;
		line->texture.y = (int)(line->currentFloor.y * tex_height) % tex_height;
		line->img = chose_gen_or_image (env, 3, 6);
		env->img_buff[line->start_y][(Uint32)ray->x] = (line->img
			[tex_width * line->texture.y + line->texture.x] >> 1) & 8355711;
		line->img = chose_gen_or_image (env, 6, 3);
		env->img_buff[WIN_HEIGHT - line->start_y][(Uint32)ray->x] =
				line->img[tex_width * line->texture.y + line->texture.x];
	}
}

void			raycasting(t_env *env, Uint32 worldMap[mapWidth][mapHeight])
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
		draw_wall_line(env, worldMap, &ray, &line);
		draw_floor_celling_line(env, &ray, &line);
	}
}

