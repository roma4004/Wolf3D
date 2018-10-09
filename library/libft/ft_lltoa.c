/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lltoa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/11 16:29:00 by dromanic          #+#    #+#             */
/*   Updated: 2018/09/11 16:33:57 by dromanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_lltoa(long long n)
{
	long long	temp;
	long long	len_n;
	char		*result;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	len_n = 1;
	temp = n;
	while (temp /= 10)
		len_n++;
	result = (char *)malloc(sizeof(char) * (len_n + 1));
	if (result)
	{
		if (n == 0)
			result[0] = '0';
		if (n < 0 && (result[0] = '-') && len_n++)
			n = -n;
		result[len_n] = '\0';
		while (n > 0 && (result[--len_n] = (n % 10 + '0')))
			n /= 10;
	}
	return (result);
}
