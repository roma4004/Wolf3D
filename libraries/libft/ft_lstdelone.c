/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/18 22:11:49 by dromanic          #+#    #+#             */
/*   Updated: 2018/11/03 11:41:21 by dromanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void	ft_lstdelone(t_list **alst, void (*del)(void *, size_t))
{
	t_list	*head;
	t_list	*cur_node;

	if (!alst || !del || !(head = *alst))
		return ;
	if (head)
	{
		cur_node = head->next;
		del(head, head->content_size);
		head = cur_node;
	}
	*alst = NULL;
}
