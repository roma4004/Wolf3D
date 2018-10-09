/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/18 21:05:53 by dromanic          #+#    #+#             */
/*   Updated: 2017/11/25 22:08:07 by dromanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncat(char *dest, const char *src, size_t n)
{
	unsigned int	i;
	unsigned int	j;

	if (n > 0)
	{
		i = ft_strlen(dest);
		j = 0;
		while (src[j] && j < n)
			dest[i++] = src[j++];
		dest[i] = '\0';
	}
	return (dest);
}
