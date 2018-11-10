/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_word_len.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/18 21:31:13 by dromanic          #+#    #+#             */
/*   Updated: 2018/11/02 18:23:26 by dromanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_word_len(const char *str, char c)
{
	size_t	len;

	if (!str)
		return (0);
	len = 0;
	while (str[len] && str[len] != c)
		len++;
	return (len);
}
