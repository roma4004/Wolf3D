/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/18 21:58:00 by dromanic          #+#    #+#             */
/*   Updated: 2017/11/19 16:21:50 by dromanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;
	char	*ch_src;
	char	*ch_dst;

	ch_src = (char *)src;
	ch_dst = (char *)dest;
	i = 0;
	while (i < n && sizeof(ch_src) <= sizeof(ch_dst))
	{
		ch_dst[i] = ch_src[i];
		i++;
	}
	return (ch_dst);
}
