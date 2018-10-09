/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/18 21:22:26 by dromanic          #+#    #+#             */
/*   Updated: 2017/11/25 21:40:45 by dromanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_strcmp(const char *s1, const char *s2)
{
	unsigned int i;
	unsigned int j;

	i = 0;
	j = 0;
	while (s1[i] == s2[j])
	{
		if (s1[i++] == '\0' || s2[j++] == '\0')
			return (0);
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[j]);
}
