/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/18 20:51:09 by dromanic          #+#    #+#             */
/*   Updated: 2018/11/03 12:37:10 by dromanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*alloc;

	if (!s)
		return (NULL);
	if ((alloc = (char *)malloc(sizeof(char) * (len + 1))))
	{
		i = 0;
		while (len--)
		{
			alloc[i] = s[start + i];
			i++;
		}
		alloc[i] = '\0';
		return (alloc);
	}
	return (NULL);
}
