/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_words.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/23 17:46:00 by dromanic          #+#    #+#             */
/*   Updated: 2018/11/03 14:06:41 by dromanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "string.h"

size_t	ft_count_words(const char *str, size_t max_i, char separator)
{
	size_t	i;
	size_t	num;

	if (str == NULL)
		return (0);
	i = 0;
	num = 0;
	if (str[0] != separator)
		++num;
	while (++i < max_i && str[i])
		if (str[i] != separator && str[i - 1] == separator)
			++num;
	return (num);
}
