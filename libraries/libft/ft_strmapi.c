/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/18 20:55:19 by dromanic          #+#    #+#             */
/*   Updated: 2018/11/02 20:24:01 by dromanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	i;
	char	*alloc;

	if (!s || !f)
		return (NULL);
	if ((alloc = ft_strnew(ft_strlen(s))))
	{
		i = -1;
		while (s[++i])
			alloc[i] = f(i, s[i]);
	}
	return (alloc);
}
