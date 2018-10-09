/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/18 22:00:54 by dromanic          #+#    #+#             */
/*   Updated: 2017/11/19 18:32:25 by dromanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	size_t	i;
	char	*ch_src;
	char	*ch_dst;

	ch_src = (char *)src;
	ch_dst = (char *)dest;
	i = 0;
	while (i < n)
	{
		ch_dst[i] = ch_src[i];
		if (ch_dst[i] == (char)c)
			return (dest + i + 1);
		i++;
	}
	return (NULL);
}
