/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/18 22:10:50 by dromanic          #+#    #+#             */
/*   Updated: 2017/11/29 19:48:47 by dromanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list *new_list;

	if (lst == NULL || f == NULL)
		return (NULL);
	new_list = NULL;
	if (lst)
	{
		new_list = (t_list *)malloc(sizeof(f(lst)));
		if (new_list)
		{
			new_list = f(lst);
			new_list->next = ft_lstmap(lst->next, f);
		}
	}
	return (new_list);
}
