/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/18 20:42:48 by dromanic          #+#    #+#             */
/*   Updated: 2017/11/26 19:17:46 by dromanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t n)
{
	size_t	i;
	size_t	len;

	i = 0;
	if (*needle == '\0')
		return ((char *)haystack);
	len = ft_strlen(needle);
	while (haystack[i] != '\0' && len <= n--)
	{
		if (haystack[i] == *needle
		&& ft_memcmp(haystack + i, needle, len) == 0)
			return ((char *)(haystack + i));
		i++;
	}
	return (NULL);
}
