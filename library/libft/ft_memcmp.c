/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/18 21:58:59 by dromanic          #+#    #+#             */
/*   Updated: 2017/11/26 22:44:14 by dromanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

int		ft_memcmp(const void *memptr1, const void *memptr2, size_t num)
{
	size_t			i;
	unsigned char	*str1;
	unsigned char	*str2;

	if (memptr1 == memptr2 || num == 0)
		return (0);
	str1 = (unsigned char *)memptr1;
	str2 = (unsigned char *)memptr2;
	i = 0;
	while (num--)
	{
		if (str1[i] != str2[i])
			return (str1[i] - str2[i]);
		if (num)
			i++;
	}
	return (0);
}
