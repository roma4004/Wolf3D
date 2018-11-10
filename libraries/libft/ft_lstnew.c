/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/18 22:07:21 by dromanic          #+#    #+#             */
/*   Updated: 2018/11/05 13:23:24 by dromanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

t_list		*ft_lstnew(void const *content, size_t content_size)
{
	t_list *new_list;

	if (!(new_list = (t_list *)malloc(sizeof(t_list))))
		return (NULL);
	new_list->content_size = (content) ? content_size : 0;
	if (content || (new_list->content = NULL))
	{
		if ((new_list->content = malloc(content_size)))
			ft_memcpy(new_list->content, content, content_size);
		else
			ft_memdel((void **)&new_list);
	}
	new_list->next = NULL;
	return (new_list);
}
