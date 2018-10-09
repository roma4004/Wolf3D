/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/18 21:23:51 by dromanic          #+#    #+#             */
/*   Updated: 2017/11/25 19:48:38 by dromanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_strdup(const char *s1)
{
	size_t	len;
	size_t	i;
	char	*new_str;

	len = 0;
	while (s1[len])
		len++;
	new_str = NULL;
	new_str = (char *)malloc(len + 1);
	if (new_str)
	{
		i = 0;
		while (i < len)
		{
			new_str[i] = s1[i];
			i++;
		}
		new_str[i] = '\0';
	}
	return (new_str);
}
