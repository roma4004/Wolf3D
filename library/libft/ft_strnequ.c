/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnequ.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/18 21:02:52 by dromanic          #+#    #+#             */
/*   Updated: 2017/11/25 15:19:12 by dromanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

int		ft_strnequ(char const *s1, char const *s2, size_t n)
{
	unsigned int	i;

	if (s1 && s2 && n > 0)
	{
		i = 0;
		while (s1[i] && s2[i] && i < n)
		{
			if (s1[i] != s2[i])
				return (0);
			i++;
		}
		if (s1[i] != s2[i] && i < n)
			return (0);
	}
	return (1);
}
