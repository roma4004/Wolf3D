/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnequ.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/18 21:02:52 by dromanic          #+#    #+#             */
/*   Updated: 2018/11/03 12:00:35 by dromanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

int		ft_strnequ(char const *s1, char const *s2, size_t n)
{
	size_t	i;

	if (!s1 || !s2 || n <= 0)
		return (1);
	i = -1;
	while (s1[++i] && s2[i] && i < n)
		if (s1[i] != s2[i])
			return (0);
	if (s1[i] != s2[i] && i < n)
		return (0);
	return (1);
}
