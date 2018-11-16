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

#include "../includes/main.h"

static void		set_texture_pixel(t_env *env, t_ray *ray,
									t_line *line, t_flags *flags)
{
	double pxs;
	int walls;
	if (flags->is_compass_texture)
	{
	 	line->tex_num = line->side;
		if (line->side == 0 && ray->dir.x > 0)
			line->tex_num = 0;
	 	else if (line->side == 0 && ray->dir.x < 0)
	 		line->tex_num += 2;
	 	else if (line->side == 1 && ray->dir.y > 0)
	 		line->tex_num += 3;
	 	else if (line->side == 1 && ray->dir.y < 0)
	 		line->tex_num += 4;
	}
	if (line->tex_num > TEXTURES - 1)
		line->tex_num %= TEXTURES - 1;
	//line->tex_num = 1;
	pxs = 0;
	walls = 0;
	while (++line->start_y < line->end_y)
	{
		line->img = flags->mode == 1 ? env->gen_tex[line->tex_num]
									: env->img_tex[line->tex_num]->pixels;
		//line->scale = line->start_y * 256 - env->win_height_x128
		//							+ (Uint32)line->h * 128;
		//line->tex_y = line->scale * TEX_HEIGHT / (Uint32)line->h / 256;
		line->scale = ((double)(line->h / env->wall_count) / TEX_HEIGHT);
		//(pxs / line->scale > TEX_HEIGHT) ? psx -= TEX_HEIGHT : pxs;
		if (pxs / line->scale >= TEX_HEIGHT)
			pxs = 1;
		line->tex_y = pxs / line->scale;
		line->color = line->img[TEX_HEIGHT * line->tex_y + line->texture.x];
		//(line->side) ? line->color = (line->color >> 1) & 8355711 : 0;
		if (line->start_y < WIN_HEIGHT && line->start_y >= 0)
			env->buff[line->start_y][line->x] = line->color;
		pxs++;
	}
}

static void		painting(t_env *env, t_ray *ray, t_line *line, Uint32 **map)
{
	//line->start_y = line->end_y - ((line->end_y - line->start_y));
	if (env->flags.mode)
	{
		line->tex_num = map[ray->pos.x][ray->pos.y] - 1;
		ray->wall_x = (line->side == 0) ? env->cam.pos.y + line->normal
					* ray->dir.y : env->cam.pos.x + line->normal * ray->dir.x;
		ray->wall_x -= (Sint32)ray->wall_x;
		line->texture.x = (Uint32)(ray->wall_x * (double)TEX_HEIGHT);
		if ((!line->side && ray->dir.x > 0) || (line->side && ray->dir.y < 0))
			line->texture.x = TEX_WIDTH - line->texture.x - 1.0;
		while (++line->start_y < line->end_y)
		{
			//if (line->start_y < WIN_HEIGHT && line->start_y >= 0)
				set_texture_pixel(env, ray, line, &env->flags);
		}
	}
	else
		while (++line->start_y < line->end_y)
		{
			if (line->start_y < WIN_HEIGHT && line->start_y >= 0)
			env->buff[line->start_y][line->x] =
				chose_color(map[ray->pos.x][ray->pos.y], (bool)line->side);
		}
}

void		draw_celling_line(t_env *env, t_ray *ray, t_line *line, t_flags *fl)
{
	/*Sint32 center = (WIN_HEIGHT >> 1);
	Sint32 start = line->end_y - line->h;
	if (start < center)
	{
		line->start_y = center + (center - start);
		printf("Start:%d|||NewStart:%d || End:%d || NewEnd:%d || Height:%d || Center:%d\n", 
			start, line->start_y - line->h, line->end_y, line->start_y, line->h, center);
	}
	else
		line->start_y = (line->end_y - env->cam.y_offset - 1);*/
	//	line->start.y = ray->pos.y + ((line->side && ray->dir.y < 0) ? 1 : 0);
	//	line->start_y = center - (line->start_y - center);
	line->start.x = ray->pos.x + ((!line->side && ray->dir.x < 0) ? 1 : 0);
	(!line->side && ray->dir.x != 0) ? line->start.y += ray->wall_x : 0;
	(line->side && ray->dir.y != 0) ? line->start.x += ray->wall_x : 0;
	line->start_y = line->end_y - line->h - env->cam.y_offset + 1;
	//line->start_y += line->h;
	//line->start_y -= line->start_y * env->cam->z - line->start_y;
	while (--line->start_y >= 0 - abs(env->cam.y_offset))
	{
		line->current_dist = WIN_HEIGHT / (2.0 * line->start_y - WIN_HEIGHT);
		line->weight = line->current_dist / line->normal;
		line->coords.x = line->weight * line->start.x
			+ (1 - line->weight) * env->cam.pos.x;
		line->coords.y = line->weight * line->start.y
			+ (1 - line->weight) * env->cam.pos.y;
		line->texture.x = (int)(line->coords.x * TEX_WIDTH) % TEX_WIDTH;
		line->texture.y = (int)(line->coords.y * TEX_HEIGHT) % TEX_HEIGHT;
		line->img = fl->mode == 2 ? env->img_tex[3]->pixels : env->gen_tex[6];
		if (line->start_y + env->cam.y_offset < line->end_y - line->h + 1 && line->start_y + env->cam.y_offset >= 0 &&
			line->start_y + env->cam.y_offset < WIN_HEIGHT)
		env->buff[line->start_y + env->cam.y_offset][(Uint32)ray->x] = fl->mode == 0 ? 0xBBBBBB :  0xBBBBBB;
			//: (line->img[TEX_WIDTH * line->texture.y + line->texture.x] >> 1);
	}
}

static void		draw_floor_line(t_env *env, t_ray *ray,
										t_line *line, t_flags *fl)
{
	line->start.x = ray->pos.x + ((!line->side && ray->dir.x < 0) ? 1 : 0);
	line->start.y = ray->pos.y + ((line->side && ray->dir.y < 0) ? 1 : 0);
	(!line->side && ray->dir.x != 0) ? line->start.y += ray->wall_x : 0;
	(line->side && ray->dir.y != 0) ? line->start.x += ray->wall_x : 0;
	line->start_y = line->end_y - env->cam.y_offset - 1;
	while (++line->start_y < WIN_HEIGHT + abs(env->cam.y_offset))
	{
		line->current_dist = WIN_HEIGHT / (2.0 * line->start_y - WIN_HEIGHT);
		line->weight = line->current_dist / line->normal;
		line->coords.x = line->weight * line->start.x
			+ (1.0 - line->weight) * env->cam.pos.x;
		line->coords.y = line->weight * line->start.y
			+ (1.0 - line->weight) * env->cam.pos.y;
		line->texture.x = (int)(line->coords.x * TEX_WIDTH) % TEX_WIDTH;
		line->texture.y = (int)(line->coords.y * TEX_HEIGHT) % TEX_HEIGHT;
		line->img = fl->mode == 2 ? env->img_tex[6]->pixels : env->gen_tex[3];
		if (line->start_y + env->cam.y_offset < WIN_HEIGHT && line->start_y + env->cam.y_offset >= 0)
		env->buff[line->start_y + env->cam.y_offset][(Uint32)ray->x] = fl->mode == 0 ? 0x424242 : 0x424242;
			//: (line->img[TEX_WIDTH * line->texture.y + line->texture.x] >> 1) & 8355711;
		line->img = fl->mode == 2 ? env->img_tex[3]->pixels : env->gen_tex[6];
	/*	if (WIN_HEIGHT - line->start_y + env->cam.y_offset < WIN_HEIGHT && WIN_HEIGHT - line->start_y + env->cam.y_offset >= 0)
		env->buff[WIN_HEIGHT - line->start_y + env->cam.y_offset][(Uint32)ray->x] =
			fl->mode == 0 ? 0x7e00ff :
				line->img[TEX_WIDTH * line->texture.y + line->texture.x];*/
	}
	draw_celling_line(env, ray, line, fl);
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
	line->height = (Sint32)(WIN_HEIGHT / line->normal);
	line->half = ((Sint32)line->height >> 1);
	line->start_y = -line->half + cam->center.y + env->cam.y_offset;
	line->end_y = line->half + cam->center.y + env->cam.y_offset;
	line->start_y += line->end_y * env->cam.z - line->end_y;
	line->end_y *= env->cam.z;
	//env->cam.y_offset = ;
	//line->start_y += line->start_y - (line->start_y * env->cam->z);
	line->start_y -= line->height * (env->wall_count - 1);
	line->x = (Uint32)ray->x;
	line->h = line->end_y - line->start_y;
	painting(env, ray, line, map);
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
		env->cam.x = 2 * ray.x / (double)WIN_WIDTH - 1;
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
		env->wall_count = 2;
		draw_wall_line(env, map, &ray, &line);
		//draw_celling_line(env, &ray, &line, &env->flags);
		draw_floor_line(env, &ray, &line, &env->flags);
	}
}
