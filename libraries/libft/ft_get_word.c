/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_word.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/19 17:08:30 by dromanic          #+#    #+#             */
/*   Updated: 2018/11/03 13:54:33 by dromanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_get_word(const char *str, size_t *str_i, char c)
{
	char	*word;
	int		i;

	if (!str || !str_i)
		return (NULL);
	if (!(word = (char *)malloc(sizeof(char) * (ft_word_len(str + *str_i, c)))))
		return (NULL);
	i = 0;
	while (str[*str_i] != c && str[*str_i])
		word[i++] = str[(*str_i)++];
	word[i] = '\0';
	return (word);
}
