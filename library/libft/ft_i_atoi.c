/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_i_atoi.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/15 16:10:00 by dromanic          #+#    #+#             */
/*   Updated: 2018/11/03 22:31:11 by dromanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long long	ft_i_atoi(const char *str, size_t *i, size_t max_i)
{
	int					sign;
	unsigned long long	result;

	sign = 1;
	result = 0;
	while (*i < max_i
	&& (str[*i] == '\t' || str[*i] == '\n' || str[*i] == '\r'
		|| str[*i] == ' ' || str[*i] == '\v' || str[*i] == '\f'))
		(*i)++;
	if (*i < max_i)
	{
		if (str[*i] == '-')
			sign = -1;
		if (str[*i] == '-' || str[*i] == '+')
			(*i)++;
	}
	while (*i < max_i && ft_isdigit(str[*i]))
		result = result * 10 + (int)str[(*i)++] - '0';
	return (result * sign);
}
