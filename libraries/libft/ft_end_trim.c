/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_end_trim.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/18 22:25:04 by dromanic          #+#    #+#             */
/*   Updated: 2018/11/03 13:57:52 by dromanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_end_trim(const char *str)
{
	size_t len;

	if (!str)
		return (0);
	len = ft_strlen(str);
	while (str[len] == ' ' || str[len] == '\t' || str[len] == '\n')
		--len;
	return (len);
}
