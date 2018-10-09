/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/18 21:19:41 by dromanic          #+#    #+#             */
/*   Updated: 2017/11/19 17:30:26 by dromanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	unsigned int	i;
	unsigned int	len;

	if (s && f)
	{
		i = 0;
		len = 0;
		while (s[len])
			len++;
		while (i < len)
		{
			f(i, &s[i]);
			i++;
		}
	}
}
