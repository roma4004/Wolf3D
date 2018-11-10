/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/18 21:04:32 by dromanic          #+#    #+#             */
/*   Updated: 2018/11/02 21:13:36 by dromanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strmap(char const *s, char (*f)(char))
{
	size_t	i;
	char	*alloc;

	if (!s || !f)
		return (NULL);
	if ((alloc = ft_strnew(ft_strlen(s))))
	{
		i = 0;
		while (s[i])
		{
			alloc[i] = f(s[i]);
			i++;
		}
	}
	return (alloc);
}
