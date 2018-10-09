/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/18 20:25:10 by dromanic          #+#    #+#             */
/*   Updated: 2017/11/29 16:31:47 by dromanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	**ft_strsplit(char const *s, char c)
{
	size_t	i;
	size_t	j;
	size_t	str_num;
	char	**alloc_arr;

	i = 0;
	j = 0;
	if (s == NULL)
		return (0);
	str_num = ft_split_count_str(s, c);
	if (!(alloc_arr = (char **)malloc(sizeof(char *)
		* str_num + sizeof(char *))))
		return (NULL);
	while (s[i] == c && s[i])
		i++;
	while (j < str_num && s[i])
	{
		alloc_arr[j] = ft_get_word(s, &i, c);
		j++;
	}
	alloc_arr[j] = NULL;
	return (alloc_arr);
}
