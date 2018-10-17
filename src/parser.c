/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/17 15:21:59 by dromanic          #+#    #+#             */
/*   Updated: 2018/10/17 17:54:56 by dromanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

//static int	convert_map(t_env *env, t_list *lst)
//{
//	t_list	*cur;
//	char	*str;
//	size_t	i;
//	int		y;
//	int		x;
//
//	if (!env || !(cur = lst))
//		return (1);
//	y = -1;
//	if ((env->map = (t_wall **)malloc(sizeof(t_wall *) * env->param->rows)))
//		while (cur && cur->content && (str = (char *)cur->content))
//		{
//			if ((x = -1) &&
//			!(env->map[++y] = (t_wall *)malloc(sizeof(t_wall) * env->param->cols)))
//				return (1);
//			i = -1;
//			while (++i < cur->content_size)
//			{
//				set_vec(env, ++x, y, ft_i_atoi(str, &i, cur->content_size));
//				env->map[y][x].color =
//						get_col(env, str + i, &i, cur->content_size);
//			}
//			cur = cur->next;
//		}
//	return (0);
//}
//
//static int	get_map_param(t_env *env, t_list *lst)
//{
//	t_list *cur;
//	size_t width;
//
//	if (!(cur = lst) || !env)
//		return (1);
//	while (cur)
//	{
//		if (!is_valid_row(env, cur->content, cur->content_size))
//			break ;//bug, erorr validation map
//		width = ft_cnt_words((char *)cur->content, cur->content_size, ' ');
//		if (env->param->cols == 0)
//			env->param->cols = width;
//		else if (env->param->cols != width && !WIDTH_ERR_SKIP)
//			env->flags->error_code = WIDTH_ERR;
//		cur = cur->next;
//	}
//	if (env->param->cols == 0 && !WIDTH_ERR_SKIP)
//	{
//		env->flags->error_code = WIDTH_ERR;
//		return (1);
//	}
//	env->param->centr_y = env->param->rows / 2;
//	env->param->centr_x = env->param->cols / 2;
//	return (0);
//}
//
//int			is_valid_row(t_env *env, void *cont, size_t max_i)
//{
//	size_t	i;
//	char	*str;
//
//	if (!env || !(str = (char *)cont))
//		return (0);
//	i = -1;
//	while (str && i < max_i)
//		if ((!(str[++i] >= '0' && str[i] <= '9')
//		|| !(str[i] == ' ')
//		|| !(str[i] == ',')
//		|| !(str[i] >= 'A' && str[i] <= 'F')))
//			env->flags->error_code = MAP_INVALID;
//	if (env->flags->error_code)
//		return (0);
//	return (1);
//}
//
//t_env		*parse_map(char *file_name, t_env *env)
//{
//	int		fd;
//	t_list	*lst;
//	char	*buf;
//
//	if (!env || !file_name)
//		return (NULL);
//	lst = NULL;
//	if ((fd = open(file_name, O_RDONLY)) == -1 || errno == ITS_A_DIRECTORY)
//	{
//		env->flags->error_code = READ_ERR;
//		return (NULL);
//	}
//	while (get_next_line(fd, &buf) > 0
//	&& (ft_append_or_new_lst(&lst, buf, ft_strlen(buf)))
//	&& (++env->param->rows))
//		ft_memdel((void *)&buf);
//	close(fd);
//	if (lst == NULL && !(errno) && !WIDTH_ERR_SKIP)
//		env->flags->error_code = WIDTH_ERR;
//	if (get_map_param(env, lst) || env->flags->error_code
//	|| convert_map(env, lst) || ft_destroy_lst(lst))
//		return (NULL);
//	return (env);
//}