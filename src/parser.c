/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/17 15:21:59 by dromanic          #+#    #+#             */
/*   Updated: 2018/10/18 20:27:08 by dromanic         ###   ########.fr       */
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
	y = -1;
	if ((env->map = malloc(sizeof(t_wall *) * env->map_height)))
		while (cur && (str = (char *)cur->content))
		{
			x = -1;
			if (!(env->map[++y] = malloc(sizeof(t_wall) * env->map_width)))
				return (1);
			i = 0;
			while (i < cur->content_size)
			{
				env->map[y][x++].tex_id =
						(Uint32)ft_i_atoi(str, &i, cur->content_size);
				i++;
			}
			cur = cur->next;
		}
	return (0);
}

static int	is_valid_row(t_env *env, void *cont, size_t max_i)
{
	size_t	i;
	char	*str;

	if (!env || !(str = (char *)cont))
		return (0);
	i = -1;
	while (str && i < max_i)
		if ((!(str[++i] >= '0' && str[i] <= '9')
			 || !(str[i] == ' ')
			 || !(str[i] == ',')
			 || !(str[i] >= 'A' && str[i] <= 'F')))
			env->error_code = MAP_INVALID;
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
			env->map_width = width;
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
	if (get_map_param(env, lst) || env->error_code
	|| convert_map(env, lst) || ft_destroy_lst(lst))
		return (NULL);
	return (env);
}
