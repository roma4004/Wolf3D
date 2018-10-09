/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/18 20:51:09 by dromanic          #+#    #+#             */
/*   Updated: 2017/11/26 19:43:29 by dromanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*alloc;

	alloc = NULL;
	if (s)
	{
		alloc = (char *)malloc(sizeof(char) * (len + sizeof(char)));
		if (alloc)
		{
			i = 0;
			while (len--)
			{
				alloc[i] = s[start + i];
				i++;
			}
			alloc[i] = '\0';
		}
	}
	return (alloc);
}
