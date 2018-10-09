/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_count_str.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/18 21:31:13 by dromanic          #+#    #+#             */
/*   Updated: 2017/11/26 21:46:09 by dromanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

int		ft_split_count_str(char const *s, char c)
{
	unsigned int i;
	unsigned int str_cnt;

	i = 0;
	str_cnt = 0;
	if (s == NULL)
		return (0);
	while (s[i])
	{
		if (s[i] == c && s[i + 1] != c)
			str_cnt++;
		i++;
	}
	if (s[0] != '\0')
		str_cnt++;
	return (str_cnt);
}
