/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/18 22:05:43 by dromanic          #+#    #+#             */
/*   Updated: 2017/11/25 19:31:55 by dromanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*ch;

	ch = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		if (ch[i] == (unsigned char)c)
			return (ch + i);
		i++;
	}
	return (NULL);
}
