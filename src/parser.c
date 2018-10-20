/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/17 15:21:59 by dromanic          #+#    #+#             */
/*   Updated: 2018/10/20 19:46:39 by dromanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static int	convert_to_map(t_list *lst, t_map *map)
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
					(Uint32)ft_i_atoi(s, &i,cur->content_size);
			cur = cur->next;
		}
	return (0);
}

static int	get_map_param(t_env *env, t_map *map, t_list *lst)
{//again need to check
	t_list	*cur;
	char	*str;
	Uint32	i;
	Uint32	width;

	if (!(cur = lst) || !env)
		return (1);
	while (cur && (str = cur->content) && (i = (Uint32)cur->content_size))
	{
		while (str && i && i--)
			if (str[i] != ' ' && !ft_isdigit(str[i]))
				env->error_num = MAP_ERR;
		width = (Uint32)ft_cnt_words(str, cur->content_size, ' ');
		if (map->width == 0)
			map->width = width;
		else if (map->width != width)
			env->error_num = WIDTH_ERR;
		cur = cur->next;
	}
	if ((map->height < 3 || map->width < 3) && (env->error_num = MAP_ERR))
		return (1);
	map->center.y = map->height / 2;
	map->center.x = map->width / 2;
	return (0);
}

Uint32		find_player_repair_map(t_env *env, t_double_pt *cam_pos,
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
	}//	printf("height=%d width=%d\n", env->map.height, env->map.width);
	return (0);
}
//9 9 9
//9 9 9
//9 9 9
//calc empty space
static int	print_map(t_map *map)
{
	Uint32	y;
	Uint32	x;
	Uint32	**map_val;

	if (!map || !DEBUG)
		return (1);
	map_val = map->tex_id;
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

t_env		*parse_map(char *file_name, t_env *env)
{
	int		fd;
	char	*buf;
	t_list	*lst;

	if (!env || !file_name || (lst = NULL))
		return (NULL);
	if ((fd = open(file_name, O_RDONLY)) == -1 || errno == ITS_A_DIRECTORY)
	{
		env->error_num = READ_ERR;
		return (NULL);
	}
	while (get_next_line(fd, &buf) > 0
	&& (ft_append_or_new_lst(&lst, buf, ft_strlen(buf))) && (++env->map.height))
		ft_memdel((void *)&buf);
	close(fd);
	if (lst == NULL && !(errno))
		env->error_num = MAP_ERR;
	if (get_map_param(env, &env->map, lst) || env->error_num
	|| convert_to_map(lst, &env->map) || ft_destroy_lst(lst)
	|| find_player_repair_map(env, &env->cam.pos, env->map.tex_id,
		(Uint32)DEF_EDGE_TEX < (Uint32)TEXTURES ? (Uint32)DEF_EDGE_TEX : 1)
	|| print_map(&env->map)
	|| ((env->cam.pos.x == 0 || env->cam.pos.x == 0) && (env->error_num = SPACE)))
		return (NULL);
	return (env);
}
