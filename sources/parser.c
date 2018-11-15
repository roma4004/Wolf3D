/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/17 15:21:59 by dromanic          #+#    #+#             */
/*   Updated: 2018/10/24 17:37:01 by dromanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

static int			convert_to_map(t_list *lst, t_map *map)
{
	t_list	*cur;
	char	*s;
	size_t	i;
	Uint32	y;
	Uint32	x;

	if (!map || !(cur = lst))
		return (1);
	y = (Uint32)-1;
	if ((map->tex_id = malloc(sizeof(Uint32 *) * map->height)))
		while (cur && (s = cur->content))
		{
			x = 0;
			if (!(map->tex_id[++y] = malloc(sizeof(Uint32) * map->width)))
				return (1);
			i = (size_t)-1;
			while (++i < cur->content_size)
				map->tex_id[y][x++] =
					(Uint32)ft_i_atoi(s, &i, cur->content_size);
			cur = cur->next;
		}
	return (0);
}

static int			get_map_param(t_env *env, t_map *map, t_list *lst)
{
	t_list	*cur;
	char	*str;
	Uint32	i;
	Uint32	width;

	if (!env || !map || !(cur = lst))
		return (1);
	while (cur && (str = cur->content))
	{
		i = (Uint32)cur->content_size;
		while (str && i && i--)
			if (str[i] != ' ' && !ft_isdigit(str[i]) && (env->err_id = MAP_ERR))
				return (1);
		width = (Uint32)ft_count_words(str, cur->content_size, ' ');
		if ((map->width == 0 && !(map->width = width))
		|| (map->width != width && (env->err_id = MAP_SIZE_ERR)))
			return (1);
		cur = cur->next;
	}
	if ((map->height < 3 || map->width < 3 || map->height > MAX_MAP_SIDE
		|| map->width > MAX_MAP_SIDE) && (env->err_id = MAP_SIZE_ERR))
		return (1);
	map->center.y = map->height >> 1;
	map->center.x = map->width >> 1;
	return (0);
}

static Uint32		find_player_map_repair(t_env *env, t_double_pt *cam_pos,
											Uint32 **map, Uint32 def_texture)
{
	Uint32	x;
	Uint32	y;

	if (!env || !map)
		return (1);
	y = (Uint32)-1;
	while (++y < env->map.height && (x = (Uint32)-1))
	{
		(!map[y][0] || map[y][0] > TEXTURES) ? map[y][0] = def_texture : 0;
		while (++x < env->map.width - 1)
		{
			if (y && y != env->map.height - 1
			&& (map[y][x] == 9 || ((!cam_pos->x || !cam_pos->y) && !map[y][x])))
			{
				map[y][x] = 0;
				cam_pos->x = y + 0.5;
				cam_pos->y = x + 0.5;
			}
			if (map[y][x] > TEXTURES
			|| ((y == 0 || y == env->map.height - 1) && !map[y][x]))
				map[y][x] = def_texture;
		}
		(!map[y][x] || map[y][x] > TEXTURES) ? map[y][x] = def_texture : 0;
	}
	return (0);
}

static int			print_map(t_map *map, Uint32 **map_val)
{
	Uint32	y;
	Uint32	x;

	if (!map)
		return (1);
	if (!DEBUG)
		return (0);
	SDL_Log("height=%d width=%d\n", map->height, map->width);
	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			ft_putnbr(map_val[y][x]);
			ft_putchar(' ');
			x++;
		}
		ft_putchar('\n');
		y++;
	}
	return (0);
}

t_env				*parse_map(char *file_name, t_env *env)
{
	int		fd;
	char	*buf;
	t_list	*lst;

	if ((!env || !file_name || (lst = NULL))
	|| (((fd = open(file_name, O_RDONLY)) == -1 || errno == ITS_A_DIRECTORY)
	&& (env->err_id = READ_ERR)))
		return (NULL);
	while (get_next_line(fd, &buf) > 0
	&& (ft_append_or_new_lst(&lst, buf, ft_strlen(buf))) && (++env->map.height))
	{
		if (env->map.height > MAX_MAP_SIDE && (env->err_id = MAP_SIZE_ERR))
			break ;
		ft_memdel((void *)&buf);
	}
	if (lst == NULL && !(errno))
		env->err_id = READ_ERR;
	if (close(fd) || get_map_param(env, &env->map, lst) || env->err_id
	|| convert_to_map(lst, &env->map) || ft_destroy_lst(lst)
	|| find_player_map_repair(env, &env->cam.pos, env->map.tex_id,
		(Uint32)DEF_EDGE_TEX < (Uint32)TEXTURES ? (Uint32)DEF_EDGE_TEX : 1)
	|| print_map(&env->map, env->map.tex_id)
	|| ((!env->cam.pos.x || !env->cam.pos.y) && (env->err_id = SPACE)))
		return (NULL);
	return (env);
}
