/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/18 22:07:21 by dromanic          #+#    #+#             */
/*   Updated: 2018/08/15 16:35:52 by dromanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static void	*ft_lst_copy_content(void const *content, size_t content_size)
{
	void	*new_content;

	if (!content)
		return (NULL);
	if ((new_content = malloc(content_size)))
		ft_memcpy(new_content, content, content_size);
	return (new_content);
}

t_list		*ft_lstnew(void const *content, size_t content_size)
{
	t_list *new_list;

	if (!(new_list = (t_list *)malloc(sizeof(t_list))))
		return (NULL);
	new_list->content = NULL;
	new_list->content_size = (content) ? content_size : 0;
	new_list->next = NULL;
	if (content)
		if (!(new_list->content = ft_lst_copy_content(content, content_size)))
			ft_memdel((void **)&new_list);
	return (new_list);
}
