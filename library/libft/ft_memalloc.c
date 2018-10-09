/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/18 22:04:48 by dromanic          #+#    #+#             */
/*   Updated: 2017/11/25 20:21:05 by dromanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	*ft_memalloc(size_t size)
{
	unsigned char	*alloc;
	size_t			i;

	if (size > 0)
	{
		alloc = NULL;
		alloc = (unsigned char *)malloc(size);
		if (alloc)
		{
			i = 0;
			while (i < size)
			{
				alloc[i] = '\0';
				i++;
			}
			return ((void *)alloc);
		}
	}
	return (NULL);
}
