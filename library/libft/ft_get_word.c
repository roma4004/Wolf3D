/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_word.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/19 17:08:30 by dromanic          #+#    #+#             */
/*   Updated: 2017/11/26 22:47:46 by dromanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_get_word(const char *str, size_t *start_iter, char c)
{
	char	*word;
	int		i;

	if (!(word = (char *)malloc(sizeof(char) * (ft_strlen(str)))))
		return (NULL);
	i = 0;
	while (str[*start_iter] != c && str[*start_iter])
	{
		word[i] = str[*start_iter];
		i++;
		*start_iter += 1;
	}
	word[i] = '\0';
	while (str[*start_iter] == c && str[*start_iter])
		*start_iter += 1;
	return (word);
}
