/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/21 20:43:55 by dromanic          #+#    #+#             */
/*   Updated: 2018/10/11 20:23:33 by dromanic         ###   ########.fr       */
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

static void		dda_line(t_env *env, Sint32 worldMap[mapWidth][mapHeight],
		double delta_distance_x, double delta_distance_y)
{
	Sint32		hit;

	hit = 0; //was there a wall hit?	//calculate step and initial sideDist
	env->step.x = (Sint32)((env->ray_direction.x < 0.0f) ? -1 : 1);
	env->step.y = (Sint32)((env->ray_direction.y < 0.0f) ? -1 : 1);
	env->ray_distance.x = delta_distance_x * ((env->ray_direction.x < 0.0f)
		? (env->pos.x - env->map_pos.x) : (env->map_pos.x + 1 - env->pos.x));
	env->ray_distance.y = delta_distance_y * ((env->ray_direction.y < 0.0f)
		? (env->pos.y - env->map_pos.y) : (env->map_pos.y + 1 - env->pos.y));
	while (hit == 0)//perform DDA
	{//jump to next map_pos square, OR in x-direction, OR in y-direction
		if (env->ray_distance.x < env->ray_distance.y)
		{
			env->ray_distance.x += delta_distance_x;
			env->map_pos.x += env->step.x;
			env->side = 0;
		}
		else
		{
			env->ray_distance.y += delta_distance_y;
			env->map_pos.y += env->step.y;
			env->side = 1;
		}
		(worldMap[env->map_pos.x][env->map_pos.y] > 0) ? hit = 1 : 0;//Check if ray has hit a wall
	}
}


void	draw_line(t_env *env, float x, Sint32 worldMap[mapWidth][mapHeight])
{
	float	lineHeight;
	float	drawStart;
	float	drawEnd;

	env->perpWallDist = (env->side == 0)
						? (env->map_pos.x - env->pos.x + (1.0f - env->step.x) / 2.0f)
						  / env->ray_direction.x
						: (env->map_pos.y - env->pos.y + (1.0f - env->step.y) / 2.0f)
						  / env->ray_direction.y;
	lineHeight = (float)(WIN_HEIGHT / env->perpWallDist);//Calculate height of line to draw on screen
	drawStart = -lineHeight / 2.0f + WIN_HEIGHT / 2.0f;//calculate lowest and highest pixel to fill in current stripe
	(drawStart < 0) ? drawStart = 0 : 0;
	drawEnd = lineHeight / 2.0f + WIN_HEIGHT / 2.0f;
	(drawEnd >= WIN_HEIGHT) ? drawEnd = WIN_HEIGHT - 1 : 0;
	//draw the pixels of the stripe as a vertical line
	while(drawStart < drawEnd)
		env->img_buff[(Sint32)drawStart++][(Sint32)x] =
				chose_color(worldMap[env->map_pos.x][env->map_pos.y], env->side);
}

void	raycasting(t_env *env, Sint32 worldMap[mapWidth][mapHeight])
{
	float	x;

	x = -1;
	while (++x < WIN_WIDTH)
	{    //calculate ray pos and direction
		env->cameraX         = 2 * x / WIN_WIDTH - 1; //x-coord in camera space
		env->ray_direction.x = env->direction.x + env->plane.x * env->cameraX;
		env->ray_direction.y = env->direction.y + env->plane.y * env->cameraX;
		env->map_pos.x       = (Sint32)env->pos.x;
		env->map_pos.y       = (Sint32)env->pos.y;
		dda_line(env, worldMap,
					fabs(1.0f / env->ray_direction.x),
					fabs(1.0f / env->ray_direction.y));
		//Calculate distance projected on camera direction
		// (Euclidean distance will give fisheye effect!)
		draw_line(env, x, worldMap);
	}
}