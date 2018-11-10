/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/15 16:12:00 by dromanic          #+#    #+#             */
/*   Updated: 2018/08/15 16:35:06 by dromanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static long long	ft_atol_base2(const char *str, int base)
{
	long long	res;
	char		*dig;
	char		*tmp;
	int			i;

	dig = "0123456789abcdefghijklmnopqrstuvwxyz";
	res = 0;
	i = 0;
	while (str[i] && (tmp = (char *)ft_memchr(dig, ft_tolower(str[i]), base)))
	{
		res = (long long int)((res * base) + (tmp - dig));
		i++;
	}
	return (res);
}

long long			ft_atol_base(const char *str, int base)
{
	long long	result;
	int			sign;
	int			i;

	i = 0;
	result = 0;
	if (!str || base < 2 || base > 36)
		return (result);
	while (str[i] == ' ' || (str[i] >= '\t' && str[i] <= '\r'))
		i++;
	sign = (base == 10 && str[i] == '-') ? -1 : 1;
	if (base == 10 && (*str == '-' || *str == '+'))
		i++;
	if (base == 16 && str[i] == '0' && ft_tolower(str[i + 1]) == 'x')
		result = ft_atol_base2(str + 2, base);
	else
		result = ft_atol_base2(str, base);
	return (result * sign);
}
