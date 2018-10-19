/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/17 15:21:59 by dromanic          #+#    #+#             */
/*   Updated: 2018/10/19 20:56:29 by dromanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static int	convert_map(t_env *env, t_list *lst)
{
	t_list	*cur;
	char	*str;
	size_t	i;
	Sint32	y;
	Sint32	x;

	if (!env || !(cur = lst))
		return (1);
	y = 0;
	if ((env->map = malloc(sizeof(Uint32 *) * env->map_height)))
		while (cur && (str = (char *)cur->content))
		{
			x = 0;
			if (!(env->map[y] = malloc(sizeof(Uint32) * env->map_width)))
				return (1);
			i = -1;
			while (++i < cur->content_size)
				env->map[y][x++] = (Uint32)ft_i_atoi(str, &i,
						cur->content_size);
			cur = cur->next;
			y++;
		}
	return (0);
}

static int	is_valid_row(t_env *env, void *cont, size_t max_i)
{
	size_t i;
	char   *str;

	if (!env || !(str = (char *)cont))
		return (0);
	i = 0;
	while (i < max_i)
	{
		if (str[i] != ' ' && str[i] != 'x' && str[i] < '0' && str[i] > '9')
			env->error_code = MAP_INVALID;
		i++;
	}
	if (env->error_code)
		return (0);
	return (1);
}

static int	get_map_param(t_env *env, t_list *lst)
{
	t_list *cur;
	size_t width;

	if (!(cur = lst) || !env)
		return (1);
	while (cur)
	{
		if (!is_valid_row(env, cur->content, cur->content_size))
			break ;//bug, erorr validation map
		width = ft_cnt_words((char *)cur->content, cur->content_size, ' ');
		if (env->map_width == 0)
			env->map_width = (Uint32)width;
		else if (env->map_width != width && !WIDTH_ERR_SKIP)
			env->error_code = WIDTH_ERR;
		cur = cur->next;
	}
	if (env->map_width == 0 && !WIDTH_ERR_SKIP)
	{
		env->error_code = WIDTH_ERR;
		return (1);
	}
	env->map_center_y = env->map_height / 2;
	env->map_center_x = env->map_width / 2;
	return (0);
}
int		print_map(t_env *env)
{
	size_t		y;
	size_t		x;

	y = 0;
	while (y < env->map_height)
	{
		x = 0;
		while (x < env->map_width)
		{
			printf("%d ", env->map[y][x]);
			x++;
		}
		printf("\n");
		y++;
	}
	return (0);
}

Uint32		map_edge_fix(t_env *env)
{
	size_t		y;
	size_t		x;
	Uint32		default_texture;

	default_texture = 1;
		//(Uint32)DEF_EDGE_TEX < (Uint32)texture_count ? (Uint32)DEF_EDGE_TEX
	//	: 1;
	y = 0;
	while (y < env->map_height)
	{
		x = 0;
		if (y == 0 || y == env->map_height)
			while (x < env->map_width)
			{
				if (env->map[y][x] == 0)
					env->map[y][x] = default_texture;
				x++;
			}
			if (x < env->map_width)
			{
				if (env->map[y][0] == 0)
					env->map[y][0] = default_texture;
				if (env->map[y][env->map_width - 1] == 0)
					env->map[y][env->map_width - 1] = default_texture;

			}
		x++;
		y++;
	}
	return (0);
}
//need check map for invalid num of texture
Uint32		place_player(t_env *env)
{
	size_t		y;
	size_t		x;

	env->cam.pos.x = 0;
	env->cam.pos.y = 0;
	y = 0;
	while (++y < env->map_height)
	{
		x = 0;
		while (++x < env->map_width)
		{
			if (env->map[y][x] == 9)
			{
				env->map[y][x] = 0;
				if (env->cam.pos.x == 0 || env->cam.pos.y == 0)
				{
					env->cam.pos.x = y + 0.5;
					env->cam.pos.y = x + 0.5;
				}
				//return (0);
			}
		}
	}
	if (env->cam.pos.x == 0 || env->cam.pos.y == 0)
	{
		y = 1;
		while (y < env->map_height)
		{
			x = 1;
			while (x < env->map_width)
			{
				if (env->map[y][x] == 0)
				{
					env->cam.pos.x = y + 0.5;
					env->cam.pos.y = x + 0.5;
					env->map[y][x] = 0;
					return (0);
				}
				x++;
			}
			y++;
		}
		//or plase in first empty space

	}
	return (0);
}

t_env		*parse_map(char *file_name, t_env *env)
{
	int		fd;
	t_list	*lst;
	char	*buf;

	if (!env || !file_name)
		return (NULL);
	lst = NULL;
	if ((fd = open(file_name, O_RDONLY)) == -1 || errno == ITS_A_DIRECTORY)
	{
		env->error_code = READ_ERR;
		return (NULL);
	}
	while (get_next_line(fd, &buf) > 0
	&& (ft_append_or_new_lst(&lst, buf, ft_strlen(buf)))
	&& (++env->map_height))
		ft_memdel((void *)&buf);
	close(fd);
	if (lst == NULL && !(errno) && !WIDTH_ERR_SKIP)
		env->error_code = WIDTH_ERR;
	if (get_map_param(env, lst)  || env->error_code
	|| convert_map(env, lst) || ft_destroy_lst(lst)
	|| map_edge_fix(env) || place_player(env) || print_map(env))
		return (NULL);
	return (env);
}
