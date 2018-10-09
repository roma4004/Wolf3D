/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/18 21:14:07 by dromanic          #+#    #+#             */
/*   Updated: 2017/11/26 18:59:34 by dromanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strjoin(char const *s1, char const *s2)
{
	unsigned int	len_s1;
	unsigned int	len_s2;
	char			*alloc;

	if (!s1 || !s2)
		return (NULL);
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	alloc = NULL;
	alloc = (char *)malloc(sizeof(char) * (len_s1 + len_s2 + 1));
	if (alloc)
	{
		ft_strcpy(alloc, s1);
		ft_strcat(alloc, s2);
	}
	return (alloc);
}
