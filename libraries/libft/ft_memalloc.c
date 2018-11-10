/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/18 22:04:48 by dromanic          #+#    #+#             */
/*   Updated: 2018/11/03 13:24:54 by dromanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void	*ft_memalloc(size_t size)
{
	unsigned char	*alloc;

	if ((size <= 0)
	|| (!(alloc = (unsigned char *)malloc(size))))
		return (NULL);
	ft_bzero(alloc, size);
	return ((void *)alloc);
}
