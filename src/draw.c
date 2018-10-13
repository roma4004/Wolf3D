/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/21 20:43:55 by dromanic          #+#    #+#             */
/*   Updated: 2018/10/13 20:16:28 by dromanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

//void		redraw(t_env *env, int img_only)
//{
//	mlx_clear_window(env->mlx_ptr, env->win_ptr);
//	mlx_put_image_to_window(env->mlx_ptr, env->win_ptr,
//							env->img->ptr, 0, 0);
//	if (!env->flags->menu_off)
//		show_menu(env, 20, 10, env->flags);
//	if (!env->flags->hints_off)
//		show_combo(env, 20, 10);
//	if (!env->flags->values_off)
//		show_values(env, 20, 10);
//	if (img_only)
//		return ;
//	if (env->param->fr_id == FR_BARNSLEY)
//	{
//		clear_img(env);
//		draw_barnsley(env, env->param);
//	}
//	else
//		parallel_draw_fractal(env);
//}

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

//static void		dda_line(t_env *env, Sint32 worldMap[mapWidth][mapHeight],
//		double delta_distance_x, double delta_distance_y)
//{
//	Sint32		hit;
//
//	hit = 0; //was there a wall hit?	//calculate step and initial sideDist
//	env->step.x = (Sint32)((env->ray_direction.x < 0.0f) ? -1 : 1);
//	env->step.y = (Sint32)((env->ray_direction.y < 0.0f) ? -1 : 1);
//	env->ray_distance.x = delta_distance_x * ((env->ray_direction.x < 0.0f)
//		? (env->pos.x - env->map_pos.x) : (env->map_pos.x + 1 - env->pos.x));
//	env->ray_distance.y = delta_distance_y * ((env->ray_direction.y < 0.0f)
//		? (env->pos.y - env->map_pos.y) : (env->map_pos.y + 1 - env->pos.y));
//	while (hit == 0)//perform DDA
//	{//jump to next map_pos square, OR in x-dir, OR in y-dir
//		if (env->ray_distance.x < env->ray_distance.y)
//		{
//			env->ray_distance.x += delta_distance_x;
//			env->map_pos.x += env->step.x;
//			env->side = 0;
//		}
//		else
//		{
//			env->ray_distance.y += delta_distance_y;
//			env->map_pos.y += env->step.y;
//			env->side = 1;
//		}
//		(worldMap[env->map_pos.x][env->map_pos.y] > 0) ? hit = 1 : 0;//Check if ray has hit a wall
//	}
//}
void		swap(Sint32 *arg1, Sint32 *arg2)
{
	Sint32	tmp;

	tmp = *arg1;
	*arg1 = *arg2;
	*arg2 = tmp;
}


void		swap_px(t_env *env, Uint32 texSize)
{//swap texture X/Y since they'll be used as vertical stripes
	Uint32	i;
	Uint32	x;
	Uint32	y;
	Sint32	tmp;

	i = 0;
	while (i < texture_count)
	{
		x = 0;
		while (x < texSize)
		{
			y = 0;
			while (y < x)
			{
				tmp = env->texture[i][texSize * y + x];
				env->texture[i][texSize * y + x] = env->texture[i][texSize * x + y];
				env->texture[i][texSize * x + y] = tmp;
				y++;
			}
			x++;
		}
		i++;
	}
//	for(size_t i = 0; i < 8; i++)
//		for(size_t x = 0; x < texSize; x++)
//			for(size_t y = 0; y < x; y++)
//				std::swap(texture[i][texSize * y + x], texture[i][texSize * x + y]);
}

static void	draw_line(t_env *env, float x, Sint32 worldMap[mapWidth][mapHeight],
		t_ray *ray)
{
	t_line	line;

	ray->hit = false;
	while (!ray->hit)
	{
		ray->x_less = ray->dist.x < ray->dist.y;
		ray->x_less ? ray->dist.x += ray->step.x : (ray->dist.y += ray->step.y);
		ray->x_less ? ray->pos.x += env->step.x : (ray->pos.y += env->step.y);
		line.side = ray->x_less ? false : true;
		(worldMap[ray->pos.x][ray->pos.y] > 0) ? ray->hit = true : 0;
	}
	line.normal = (!line.side)
				? (ray->pos.x - env->pos.x + (1 - env->step.x) / 2) / ray->dir.x
		: (ray->pos.y - env->pos.y + (1 - env->step.y) / 2) / ray->dir.y;
	line.height = WIN_HEIGHT / line.normal / 2;
	line.start  = -line.height + env->win_center.y;
	line.start < 0 ? line.start = 0 : 0;
	line.end = line.height + env->win_center.y;
	line.end >= WIN_HEIGHT ? line.end = WIN_HEIGHT - 1 : 0;
//	while (line.start < line.end)
//		env->img_buff[(Sint32)line.start++][(Sint32)x] =
//			chose_color(worldMap[ray->pos.x][ray->pos.y], line.side);


	//texturing calculations
	Sint32 texNum = worldMap[ray->pos.x][ray->pos.y] - 1; //1 subtracted from it so that texture 0 can be used!
	ray->wallX = (line.side == 0) ? env->pos.y + line.normal * ray->dir.y
									: env->pos.x + line.normal * ray->dir.x;
	ray->wallX -= floor(ray->wallX);
	Sint32 texX = (Sint32)(ray->wallX * tex_width);//x coordinate on the texture
	(line.side == 0 && ray->dir.x > 0) ? texX = tex_width - texX - 1 : 0;
	(line.side == 1 && ray->dir.y < 0) ? texX = tex_width - texX - 1 : 0;
	for (Sint32 y = (Sint32)line.start; y < line.end; y++)
	{
		Sint32 d = (Sint32)(y * 256 - WIN_HEIGHT * 128 + line.height * 128);  //256 and 128 factors to avoid floats // TODO: avoid the division to speed this up
		Sint32 texY  = (Sint32)(((d * tex_height) / line.height) / 256);//ussless () in (d * tex_height) need to  check it
		Sint32 color = (Sint32)(env->texture[texNum][tex_height * texY + texX]);
		(line.side) ? color = (color >> 1) & 8355711 : 0;//8355711 make color darker for y-sides: R, G and B byte each
		// divided through two with a "shift" and an "and"
		//env->buffer[y][(Sint32)x] = color;
		env->img_buff[(Sint32)line.start++][(Sint32)x]= color;
	}
}

void		raycasting(t_env *env, Sint32 worldMap[mapWidth][mapHeight],
						double x)
{
	t_ray	ray;

	while (++x < WIN_WIDTH)
	{
		env->camera_x = 2 * x / WIN_WIDTH - 1;
		ray.dir.x = env->player_dir.x + env->plane.x * env->camera_x;
		ray.dir.y = env->player_dir.y + env->plane.y * env->camera_x;
		ray.pos.x = (Sint32)env->pos.x;
		ray.pos.y = (Sint32)env->pos.y;
		ray.step.x = fabs(1 / ray.dir.x);
		ray.step.y = fabs(1 / ray.dir.y);
		env->step.x = ray.dir.x < 0 ? -1 : 1;
		env->step.y = ray.dir.y < 0 ? -1 : 1;
		ray.dist.x = ray.step.x * (ray.dir.x < 0
			? env->pos.x - ray.pos.x : ray.pos.x + 1 - env->pos.x);
		ray.dist.y = ray.step.y * (ray.dir.y < 0
			? env->pos.y - ray.pos.y : ray.pos.y + 1 - env->pos.y);
		env->step.x = ray.dir.x < 0 ? -1 : 1;
		env->step.y = ray.dir.y < 0 ? -1 : 1;
		ray.dist.x = ray.step.x * (ray.dir.x < 0
			? env->pos.x - ray.pos.x : ray.pos.x + 1 - env->pos.x);
		ray.dist.y = ray.step.y * (ray.dir.y < 0
			? env->pos.y - ray.pos.y : ray.pos.y + 1 - env->pos.y);
		draw_line(env, x, worldMap, &ray);
	}
}

void		get_time_ticks(t_fps *fps)
{
	fps->previous_tick = fps->current_tick; // timing for input and FPS counter
	fps->current_tick = SDL_GetTicks();
	//frame_time is the current_tick this frame has taken, in seconds
	fps->frame_time = (fps->current_tick - fps->previous_tick) / 1000.f;
	//prSint32f("%f\n", 1.0 / frame_time); //FPS counter
}
