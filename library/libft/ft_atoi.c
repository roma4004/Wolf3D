/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/18 22:22:01 by dromanic          #+#    #+#             */
/*   Updated: 2017/11/29 22:02:41 by dromanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

static	int		ft_len_of_num(const char *s)
{
	int		i;
	int		len;

	i = 0;
	len = 0;
	while (s[i++])
		if (s[i] >= '0' && s[i] <= '9')
			len++;
	return (len);
}

int				ft_atoi(const char *str)
{
	int					i;
	int					sign;
	unsigned long long	result;

	i = 0;
	sign = 1;
	result = 0;
	while (str[i] == '\t' || str[i] == '\n' || str[i] == '\r' ||
			str[i] == ' ' || str[i] == '\v' || str[i] == '\f')
		i++;
	if (str[i] == '-')
		sign = -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
		result = result * 10 + (int)str[i++] - '0';
	if ((result > 9223372036854775807 && sign == 1)
		|| (ft_len_of_num(str) >= 19 && sign == 1))
		return (-1);
	if (result > 9223372036854775807 && sign == -1)
		return (0);
	return (result * sign);
}
