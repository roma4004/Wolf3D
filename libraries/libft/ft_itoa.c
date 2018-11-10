/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/18 20:01:54 by dromanic          #+#    #+#             */
/*   Updated: 2018/11/03 14:34:28 by dromanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa(int n)
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
