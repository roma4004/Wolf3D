/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/08 17:59:40 by dromanic          #+#    #+#             */
/*   Updated: 2018/11/10 19:39:35 by dromanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line2.h"

static void	ft_substr_copy2(char *dst, char *src, size_t *i, char stop_sym)
{
	size_t j;

	if (!dst || !src)
		return;
	j = 0;
	while (src[*i] && src[*i] != stop_sym)
		dst[j++] = src[(*i)++];
}

static size_t	line_len(char *str)
{
	size_t	len;

	if (!str)
		return (0);
	len = 0;
	while (*str != '\n' && *str != '\0' && ++str)
		len++;
	return (len);
}

static int	data_mod(t_list **lst, size_t fd, char *buf, size_t line_len)
{
	t_list	*cur;

	if (!buf || line_len < 1)
		return (0);
	if (!(cur = *lst))
	{
		ft_append_or_new_lst(lst, buf, ft_strlen(buf));
		(*lst)->content_size = fd;
	}
	else
	{
		while (cur)
		{
			if (cur->content_size == fd)
				break;
			cur = cur->next;
		}
		if (cur->content)
			cur->content = ft_strjoin(cur->content, buf);
		else
			ft_strdup(buf);//not checked if buffer not full
	}
	return (1);
}

static void	del_line(t_list *lst, size_t fd, size_t *offset)
{
	t_list	*pre;
	t_list	*cur;
	char	*str;

	if (!(cur = lst) || !(pre = lst))
		return ;
	while (cur)
	{
		if ((str = cur->content) && cur->content_size == (size_t)fd)
		{
			if (!ft_strchr(str, '\n'))
			{
				free(str);
				pre->next = cur->next;
				free(cur);
			}
			else
				ft_strlcat(str, str + *offset + 1, ft_strlen(str) - *offset);
			return ;
		}
		pre = cur;
		cur = cur->next;
	}
}

static int	pop_line(t_list *lst, char **line, const int fd)
{
	t_list	*cur;
	size_t	offset;

	cur = lst;
	while (cur)
	{
		if (cur->content_size == (size_t)fd)
		{
			if((*line = ft_strnew(line_len(cur->content))))
			{
				ft_substr_copy2(*line, cur->content, &offset, '\n');
				del_line(cur, fd, &offset);
				return (1);
			}
		}
		cur = cur->next;
	}
	return (0);
}

int			get_next_line(const int fd, char **line)
{
	static t_list	*lst = NULL;
	t_list			*cur;
	ssize_t			len;
	char			buf[BUFF_SIZE + 1];//need move to stack

	if (fd < 0 || BUFF_SIZE < 1 || fd > MAX_FD || (buf[BUFF_SIZE] = '\0'))
		return (-1);
	*line = NULL;
	cur = lst;
	while (cur && cur->content)
	{
		if (cur->content_size == (size_t)fd
		&& cur->content && ft_strchr(cur->content, '\n'))
			return (pop_line(lst, line, fd));
		cur = cur->next;
	}
	while ((len = read(fd, buf, BUFF_SIZE)) > 0
	&& data_mod(&lst, (size_t)fd, buf, (size_t)len) && !ft_strchr(buf, '\n'))
		ft_bzero(buf, BUFF_SIZE);
	if (len == -1)
		return (-1);
	return (pop_line(lst, line, fd));
}
