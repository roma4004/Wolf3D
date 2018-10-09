/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/18 21:55:18 by dromanic          #+#    #+#             */
/*   Updated: 2017/11/25 20:48:17 by dromanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	size_t	i;
	char	*ch_b_ptr;

	ch_b_ptr = (char *)b;
	i = 0;
	while (i < len)
	{
		ch_b_ptr[i] = c;
		i++;
	}
	return (b);
}
