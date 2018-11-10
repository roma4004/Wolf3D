/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strequ.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/18 21:16:25 by dromanic          #+#    #+#             */
/*   Updated: 2018/11/07 13:01:38 by dromanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

int		ft_strequ(char const *s1, char const *s2)
{
	size_t	i;

	if (!s1 && !s2)
		return (1);
	if (!s1 || !s2)
		return (0);
	i = -1;
	while (s1[++i] && s2[i])
		if (s1[i] != s2[i])
			return (0);
	if (s1[i] != s2[i])
		return (0);
	return (1);
}
