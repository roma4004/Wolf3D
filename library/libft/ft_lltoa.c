/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lltoa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/11 16:29:00 by dromanic          #+#    #+#             */
/*   Updated: 2018/11/03 14:51:11 by dromanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_lltoa(long long n)
{
	size_t	len;
	char	*result;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	len = ft_num_width(n);
	if ((result = ft_strnew(len)))
	{
		if (n == 0)
			result[0] = '0';
		if (n < 0 && (result[0] = '-'))
			n = -n;
		while (n > 0 && (result[--len] = (char)('0' + n % 10)))
			n /= 10;
	}
	return (result);
}
