/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/21 20:43:55 by dromanic          #+#    #+#             */
/*   Updated: 2018/10/12 20:55:39 by dromanic         ###   ########.fr       */
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

void	clear_img_buff(t_env *env)
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
		{
			env->img_buff[y][x] = 0x0;
			x++;
		}
		y++;
	}
}

void	frame_limit(Uint32 current_tick, Uint32 previous_tick)
{
	if ((1000 / FRAME_LIMIT) > current_tick - previous_tick)
		SDL_Delay(1000 / FRAME_LIMIT - (current_tick - previous_tick));
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

void	draw_line(t_env *env, float x, Sint32 worldMap[mapWidth][mapHeight],
		t_ray ray)
{
	t_line	line;

	ray.hit = 0;
	while (ray.hit == 0)
	{
		ray.less_dist = ray.dist.x < ray.dist.y;
		(ray.less_dist) ? (ray.dist.x += ray.delta_dist.x)
						: (ray.dist.y += ray.delta_dist.y);
		(ray.less_dist) ? (ray.pt.x += env->step.x)
						: (ray.pt.y += env->step.y);
		env->side = (ray.less_dist) ? 0 : 1;
		(worldMap[ray.pt.x][ray.pt.y] > 0) ? ray.hit = 1 : 0;
	}
	line.perp_wall_dist = (env->side == 0)
		? (ray.pt.x - env->pos.x + (1 - env->step.x) / 2) / ray.dir.x
		: (ray.pt.y - env->pos.y + (1 - env->step.y) / 2) / ray.dir.y;
	line.height = (float)(WIN_HEIGHT / line.perp_wall_dist);
	line.start  = -line.height / 2 + WIN_HEIGHT / 2;
	(line.start < 0) ? line.start = 0 : 0;
	line.end = line.height / 2 + WIN_HEIGHT / 2;
	(line.end >= WIN_HEIGHT) ? line.end = WIN_HEIGHT - 1 : 0;
	while(line.start < line.end)
		env->img_buff[(Sint32)line.start++][(Sint32)x] =
			chose_color(worldMap[ray.pt.x][ray.pt.y], env->side);
//
//
//	//texturing calculations
//	int texNum = worldMap[env->map_pt.x][env->map_pt.y] - 1; //1 subtracted from it so that texture 0 can be used!
//
//	//calculate value of wallX
//	double wallX; //where exactly the wall was hit
//	if (env->side == 0)
//		wallX = env->pos.y + env->perp_wall_dist * env->ray_dir.y;
//	else
//		wallX = env->pos.x + env->perp_wall_dist * env->ray_dir.x;
//	wallX -= floor((wallX));
//
//	//x coordinate on the texture
//	int texX = (int)(wallX * (double)(texWidth));
//	if (env->side == 0 && env->ray_dir.x > 0)
//		texX = texWidth - texX - 1;
//	if (env->side == 1 && env->ray_dir.y < 0)
//		texX = texWidth - texX - 1;
//	for (int y = start; y < End; y++)
//	{
//		int d = y * 256 - WIN_HEIGHT * 128 + height * 128;  //256 and 128 factors to avoid floats
//		// TODO: avoid the division to speed this up
//		int    texY  = ((d * texHeight) / height) / 256;
//		Uint32 color = env->texture[texNum][texHeight * texY + texX];
//		//make color darker for y-sides: R, G and B byte each divided through two with a "shift" and an "and"
//		if (env->side == 1)
//			color    = (color >> 1) & 8355711;
//		env->buffer[y][(int)x] = color;
//	}
}

void	raycasting(t_env *env, Sint32 worldMap[mapWidth][mapHeight], double x)
{
	t_ray	ray;

	while (++x < WIN_WIDTH)
	{
		env->camera_x = 2 * x / WIN_WIDTH - 1;
		ray.dir.x = env->direction.x + env->plane.x * env->camera_x;
		ray.dir.y = env->direction.y + env->plane.y * env->camera_x;
		ray.pt.x = (Sint32)env->pos.x;
		ray.pt.y = (Sint32)env->pos.y;
		ray.delta_dist.x = fabs(1.0f / ray.dir.x);
		ray.delta_dist.y = fabs(1.0f / ray.dir.y);
		env->step.x = (Sint32)((ray.dir.x < 0.0f) ? -1 : 1);
		env->step.y = (Sint32)((ray.dir.y < 0.0f) ? -1 : 1);
		ray.dist.x = ray.delta_dist.x * ((ray.dir.x < 0.0f)
			? (env->pos.x - ray.pt.x) : (ray.pt.x + 1 - env->pos.x));
		ray.dist.y = ray.delta_dist.y * ((ray.dir.y < 0.0f)
			? (env->pos.y - ray.pt.y) : (ray.pt.y + 1 - env->pos.y));
		env->step.x = (Sint32)((ray.dir.x < 0.0f) ? -1 : 1);
		env->step.y = (Sint32)((ray.dir.y < 0.0f) ? -1 : 1);
		ray.dist.x = ray.delta_dist.x * ((ray.dir.x < 0.0f)
			? (env->pos.x - ray.pt.x) : (ray.pt.x + 1 - env->pos.x));
		ray.dist.y = ray.delta_dist.y * ((ray.dir.y < 0.0f)
			? (env->pos.y - ray.pt.y) : (ray.pt.y + 1 - env->pos.y));
		draw_line(env, x, worldMap, ray);
	}
}

void	get_time_ticks(t_env *env)
{
	env->previous_tick = env->current_tick; // timing for input and FPS counter
	env->current_tick = SDL_GetTicks();
	//frameTime is the current_tick this frame has taken, in seconds
	env->frameTime = (env->current_tick - env->previous_tick) / 1000.0f;
	//prSint32f("%f\n", 1.0 / frameTime); //FPS counter
}

void		swap_px(t_env *env, size_t texSize)
{//swap texture X/Y since they'll be used as vertical stripes
	size_t	i;
	size_t	x;
	size_t	y;
	Sint32	tmp;

	i = 0;
	while (i < textureCount)
	{
		y = 0;
		while (x < texSize)
		{
			x = 0;
			while (y < x)
			{
				tmp = env->texture[i][texSize * y + x];
				env->texture[i][texSize * y + x] =
					env->texture[i][texSize * x + y];
				env->texture[i][texSize * x + y] = tmp;
				x++;
			}
			y++;
		}
		i++;
	}
}