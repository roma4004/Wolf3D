/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/18 20:25:10 by dromanic          #+#    #+#             */
/*   Updated: 2018/11/08 14:02:47 by dromanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	**ft_strsplit(char const *s, char c)
{
	size_t		len;
	size_t		i;
	size_t		j;
	char		**res;

	if (!s)
		return (NULL);
	len = ft_count_words(s, ft_strlen(s), c);
	if (!(res = (char **)malloc(sizeof(char *) * (len + 1))))
		return (NULL);
	i = 0;
	while (s[i] == c && s[i])
		i++;
	j = 0;
	while (j < len && s[i] && (res[j++] = ft_get_word(s, &i, c)))
		while (s[i] == c && s[i])
			i++;
	res[j] = NULL;
	return (res);
}
