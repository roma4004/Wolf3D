/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/18 21:15:25 by dromanic          #+#    #+#             */
/*   Updated: 2017/11/29 22:08:48 by dromanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>

size_t				ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	dst_end;

	if (size == 0)
		return (ft_strlen(src));
	i = 0;
	while (dst[i] && i < size)
		i++;
	dst_end = i;
	while (src[i - dst_end] && i < size - 1)
	{
		dst[i] = src[i - dst_end];
		i++;
	}
	if (dst_end < size)
		dst[i] = '\0';
	return (dst_end + ft_strlen(src));
}
