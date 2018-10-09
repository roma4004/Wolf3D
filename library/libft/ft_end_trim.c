/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_end_trim.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/18 22:25:04 by dromanic          #+#    #+#             */
/*   Updated: 2017/11/29 18:24:36 by dromanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_end_trim(const char *str)
{
	unsigned int len;

	len = 0;
	if (str)
	{
		len = ft_strlen(str) - 1;
		while (str[len] == ' ' || str[len] == '\t' || str[len] == '\n')
			len--;
	}
	return (len);
}
