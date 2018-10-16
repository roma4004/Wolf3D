/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/21 20:43:55 by dromanic          #+#    #+#             */
/*   Updated: 2018/10/16 20:41:59 by dromanic         ###   ########.fr       */
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

void		pixel_from_texture(t_env *env, t_line *line, Uint32 tex_num)
{
	tex_num %= texture_count;
	while (++line->start_y < line->end_y)
	{
		line->img = (env->tex_mode == 1) ? env->gen_texture[tex_num]
										: env->surfaces[tex_num]->pixels;
		line->scale = line->start_y * 256 - WIN_HEIGHT * 128
					  + (Uint32)line->height * 128;//TODO: avoid the division to speed this up
		line->tex_y = line->scale * tex_height / (Uint32)line->height / 256;
		line->color = line->img[tex_height * line->tex_y + line->tex_x];
		(line->side) ? line->color = (line->color >> 1) & 8355711 : 0;
		env->img_buff[line->start_y][line->x] = line->color;
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
//			line->img = (env->tex_mode == 1) ? env->gen_texture[line->tex_num]
//										: env->surfaces[line->tex_num]->pixels;
//			line->scale = line->start_y * 256 - WIN_HEIGHT * 128 +
//						(Uint32)line->height * 128;//TODO: avoid the division to speed this up
//			line->tex_y = line->scale * tex_height / (Uint32)line->height / 256;
//			line->color = line->img[tex_height * line->tex_y + line->tex_x];
//			(line->side) ? line->color = (line->color >> 1) & 8355711 : 0;
//			env->img_buff[line->start_y][line->x] = line->color;

//			line->side_offset = (ray->step.x < 0) ? 0 : 1;
//			line->side_offset = (line->side == 1 && ray->step.y < 0) ? 2 : 3;
			line->side_offset = 0;
		if(line->side == 0 && ray->dir.x > 0)
		{
			line->side_offset = 1;
		}
		else if(line->side == 0 && ray->dir.x < 0)
		{
			line->side_offset = 2;
		}
		else if(line->side == 1 &&  ray->dir.y > 0)
		{
			line->side_offset = 3;
		}
		else
		{
			line->side_offset = 4;
		}
			pixel_from_texture(env, line, line->side + line->side_offset);
//			if (env->cam.step.x < 0)
//				pixel_from_texture(env, line,  0);
//			else
//				pixel_from_texture(env, line,  1);
//			if (line->side > 1)
//			{
//				if (env->cam.step.y < 0)
//					pixel_from_texture(env, line, 2);
//				else
//					pixel_from_texture(env, line, 3);
//			}

		}
	}

	else
		while (line->start_y < line->end_y)
			env->img_buff[line->start_y++][line->x] =
				chose_color(worldMap[ray->pos.x][ray->pos.y], line->side);
}

static void	draw_line(t_env *env, Uint32 worldMap[mapWidth][mapHeight],
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
			: (ray->pos.y - cam->pos.y + ((1 - cam->step.y) >> 1)) /
			ray->dir.y;
	line->height = WIN_HEIGHT / line->normal * cam->wall_scale;
	line->half = (Uint32)line->height >> 1;
	line->start_y = (Uint32)((-line->half + cam->center.y <= 0)
			? 0 : -line->half + cam->center.y);
	line->end_y = (Uint32)((line->half + cam->center.y) >= WIN_HEIGHT
			? WIN_HEIGHT - 1 : line->half + cam->center.y);
	line->x = (Uint32)ray->x;
	painting(env, ray, line, worldMap);
}

void		raycasting(t_env *env, Uint32 worldMap[mapWidth][mapHeight])
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
		draw_line(env, worldMap, &ray, &line);

		line.floor_wall.x = ray.pos.x;
		line.floor_wall.y = ray.pos.y;
		if(!line.side && ray.dir.x < 0)
			line.floor_wall.x += 1.0;
		if (line.side && ray.dir.y < 0)
			line.floor_wall.y += 1.0;
		if ((!line.side && ray.dir.x > 0) || (!line.side && ray.dir.x < 0))
			line.floor_wall.y += ray.wall_x;
		if ((line.side && ray.dir.y > 0) || (line.side && ray.dir.y < 0))
			line.floor_wall.x += ray.wall_x;
		for(line.start_y = line.end_y + 1; line.start_y < WIN_HEIGHT; line.start_y++)
		{
			line.current_dist = WIN_HEIGHT / (2.0 * line.start_y - WIN_HEIGHT); //you could make a small lookup table for this instead
			line.weight = line.current_dist / line.normal;
			line.currentFloor.x = line.weight * line.floor_wall.x
					+ (1 / cam->wall_scale - line.weight) * env->cam.pos.x;
			line.currentFloor.y = line.weight * line.floor_wall.y
					+ (1 / cam->wall_scale - line.weight) * env->cam.pos.y;
			line.floorTex.x = (int)(line.currentFloor.x * tex_width) % tex_width;
			line.floorTex.y = (int)(line.currentFloor.y * tex_height) % tex_height;
			line.img = env->surfaces[6]->pixels;
			env->img_buff[line.start_y][(Uint32)ray.x] =
				(line.img[tex_width * line.floorTex.y + line.floorTex.x] >> 1)
					& 8355711;//floor
			line.img = env->surfaces[3]->pixels;
			env->img_buff[WIN_HEIGHT - line.start_y][(Uint32)ray.x] =
					line.img[tex_width * line.floorTex.y + line.floorTex.x];
		}
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
