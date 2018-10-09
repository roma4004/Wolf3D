/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/18 20:55:19 by dromanic          #+#    #+#             */
/*   Updated: 2017/11/29 15:33:27 by dromanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	i;
	char	*alloc;

	if (s == NULL || f == NULL)
		return (NULL);
	alloc = NULL;
	alloc = ft_strnew(ft_strlen(s));
	if (alloc)
	{
		i = 0;
		while (s[i])
		{
			alloc[i] = f(i, s[i]);
			i++;
		}
	}
	return (alloc);
}
