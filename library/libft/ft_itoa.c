/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/18 20:01:54 by dromanic          #+#    #+#             */
/*   Updated: 2018/08/15 16:35:36 by dromanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_itoa(int n)
{
	long int	temp;
	long int	len_n;
	char		*result;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	result = NULL;
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
