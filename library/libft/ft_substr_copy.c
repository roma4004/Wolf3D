/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substring_copy.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/20 14:50:10 by dromanic          #+#    #+#             */
/*   Updated: 2017/11/25 16:03:16 by dromanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	ft_substr_copy(char *dst, char *src, unsigned int *src_i, char stop_sym)
{
	unsigned int i;

	i = 0;
	if (dst && src)
	{
		while (src[*src_i] && dst[i])
		{
			if (src[*src_i] == stop_sym)
				return ;
			dst[i++] = src[*src_i++];
		}
	}
}
