/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr_copy.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/20 14:50:10 by dromanic          #+#    #+#             */
/*   Updated: 2018/11/02 19:55:44 by dromanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_substr_copy(char *dst, char *src, size_t *i, char stop_sym)
{
	size_t	j;

	if (!dst || !src)
		return ;
	j = 0;
	while (src[*i] && dst[j])
	{
		if (src[*i] == stop_sym)
			return ;
		dst[j++] = src[(*i)++];
	}
}
