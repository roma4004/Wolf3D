/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_append_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/19 16:00:41 by dromanic          #+#    #+#             */
/*   Updated: 2018/08/15 16:34:58 by dromanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

int		ft_append_or_new_lst(t_list **lst, char *buf, size_t size)
{
	t_list *cur;

	if (!(*lst))
		*lst = ft_lstnew(buf, size);
	else
	{
		cur = *lst;
		while (cur->next)
			cur = cur->next;
		cur->next = ft_lstnew(buf, size);
	}
	return (1);
}
