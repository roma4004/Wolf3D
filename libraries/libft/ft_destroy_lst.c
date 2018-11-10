/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_destroy_lst.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/15 16:00:00 by dromanic          #+#    #+#             */
/*   Updated: 2018/08/15 16:35:14 by dromanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_destroy_lst(t_list *lst)
{
	t_list	*cur;
	t_list	*tmp;

	if (!(cur = lst))
		return (1);
	while (cur)
	{
		tmp = cur->next;
		if (cur->content)
			ft_memdel(&cur->content);
		ft_memdel((void *)&cur);
		cur = tmp;
	}
	return (0);
}
