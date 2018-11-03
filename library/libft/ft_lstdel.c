/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/18 22:08:55 by dromanic          #+#    #+#             */
/*   Updated: 2017/11/29 19:50:03 by dromanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list	*head;
	t_list	*cur_node;

	if (!alst || !del || !(head = *alst))
		return ;
	while (head)
	{
		cur_node = head->next;
		del(head->content, head->content_size);
		free(head);
		head = cur_node;
	}
	*alst = NULL;
}
