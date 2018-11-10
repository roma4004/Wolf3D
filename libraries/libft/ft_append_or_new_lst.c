/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_append_or_new_lst.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/19 16:00:41 by dromanic          #+#    #+#             */
/*   Updated: 2018/11/04 12:52:35 by dromanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

int		ft_append_or_new_lst(t_list **lst, void *content, size_t content_size)
{
	t_list *cur;

	if (!(*lst))
		*lst = ft_lstnew(content, content_size);
	else
	{
		cur = *lst;
		while (cur->next)
			cur = cur->next;
		cur->next = ft_lstnew(content, content_size);
	}
	return (1);
}
