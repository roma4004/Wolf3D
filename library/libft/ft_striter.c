/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/18 21:21:31 by dromanic          #+#    #+#             */
/*   Updated: 2017/11/19 17:41:20 by dromanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striter(char *s, void (*f)(char *))
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
			f(&s[i]);
			i++;
		}
	}
}
