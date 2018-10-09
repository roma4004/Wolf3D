/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_i_atoi.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/15 16:10:00 by dromanic          #+#    #+#             */
/*   Updated: 2018/08/15 16:35:22 by dromanic         ###   ########.fr       */
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
		*i = *i + 1;
	if (*i < max_i && (str[*i] == '-'))
		sign = -1;
	if (*i < max_i && (str[*i] == '-' || str[*i] == '+'))
		*i = *i + 1;
	while (*i < max_i && str[*i] >= '0' && str[*i] <= '9')
		result = result * 10 + (int)str[(*i)++] - '0';
	if (result > 9223372036854775807U && sign == 1)
		return (-1);
	if (result > 9223372036854775808U && sign == -1)
		return (0);
	return (result * sign);
}
