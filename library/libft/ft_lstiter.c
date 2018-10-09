/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/18 22:14:14 by dromanic          #+#    #+#             */
/*   Updated: 2017/11/29 19:48:07 by dromanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(t_list *elem))
{
	t_list *curr_node;

	if (lst == NULL || f == NULL)
		return ;
	curr_node = NULL;
	if (lst)
	{
		curr_node = lst;
		while (curr_node->next)
		{
			f(curr_node);
			curr_node = curr_node->next;
		}
		f(curr_node);
	}
}
