/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/08 17:59:40 by dromanic          #+#    #+#             */
/*   Updated: 2018/08/15 16:33:49 by dromanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	ln_len(char *str)
{
	int i;
	int	len;

	if (str == NULL)
		return (0);
	i = 0;
	len = 0;
	while (str[i] != '\n' && str[i] != '\0' && str[i++] != '\3')
		len++;
	return (len);
}

static int	data_mod(char **data, int fd, char *buf, unsigned int line_len)
{
	char	*temp;

	temp = NULL;
	if (data == NULL || buf == NULL || line_len == 0)
		return (0);
	if (data[fd] == NULL)
	{
		if ((data[fd] = ft_strnew(line_len)))
			ft_strncpy(data[fd], buf, line_len);
	}
	else
	{
		temp = ft_strjoin(data[fd], buf);
		free(data[fd]);
		data[fd] = NULL;
		data[fd] = temp;
	}
	return (1);
}

static int	del_line(char **data, int fd)
{
	unsigned int	i;
	unsigned int	j;
	unsigned int	rem_size;
	char			*nline;
	int				line_len;

	if (data[fd] == NULL)
		return (0);
	nline = NULL;
	if (ft_strchr(data[fd], '\n'))
	{
		line_len = ln_len(data[fd]);
		rem_size = ft_strlen(data[fd]) - line_len - 1;
		if (rem_size > 0)
			nline = ft_strnew(rem_size);
		if (nline && (i = ln_len(data[fd]) + 1))
		{
			j = 0;
			while (data[fd][i])
				nline[j++] = data[fd][i++];
		}
	}
	free(data[fd]);
	data[fd] = nline;
	return (1);
}

static char	**init_data(void)
{
	int		i;
	char	**new_data;

	if ((new_data = (char **)malloc(sizeof(char *) * MAX_FD)))
	{
		i = 0;
		while (i < MAX_FD)
			new_data[i++] = NULL;
	}
	return (new_data);
}

int			get_next_line(const int fd, char **line)
{
	static char		**data = NULL;
	int				len;
	char			*buf;

	if (fd < 0 || fd > MAX_FD)
		return (-1);
	if (data == NULL)
		data = init_data();
	buf = ft_strnew(BUFF_SIZE);
	while ((len = read(fd, buf, BUFF_SIZE)) > 0 && data_mod(data, fd, buf, len))
	{
		if (ft_strchr(buf, '\n'))
			break ;
		ft_bzero(buf, BUFF_SIZE);
	}
	free(buf);
	if (len == -1)
		return (-1);
	if (data[fd] == NULL)
		return (0);
	*line = ft_strnew(ln_len(data[fd]));
	if ((*line) && (ft_strncpy(*line, data[fd], ln_len(data[fd]))))
		return (del_line(data, fd));
	return (0);
}
