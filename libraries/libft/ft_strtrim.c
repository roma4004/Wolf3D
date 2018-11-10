/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/18 20:23:24 by dromanic          #+#    #+#             */
/*   Updated: 2018/11/07 19:24:14 by dromanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strtrim(char const *s)
{
	ssize_t		i;
	ssize_t		len;
	char		*alloc;

	if (!s)
		return (NULL);
	len = (ssize_t)(ft_strlen(s));
	while (s[len - 1] == ' ' || s[len - 1] == '\t' || s[len - 1] == '\n')
		len--;
	i = -1;
	while (s[++i] == ' ' || s[i] == '\t' || s[i] == '\n')
		len--;
	if (len <= 0)
		len = 0;
	if (!(alloc = ft_strnew((size_t)len)))
		return (NULL);
	s += i;
	i = -1;
	while (++i < len)
		alloc[i] = *s++;
	return (alloc);
}
