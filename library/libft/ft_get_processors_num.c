/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_processors_num.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/12 12:51:00 by dromanic          #+#    #+#             */
/*   Updated: 2018/11/03 14:45:47 by dromanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <sys/param.h>
#include <sys/sysctl.h>

/*
** on macOS detecting number of processors on machine:
** <sys/param.h>, <sys/sysctl.h> needed for int func get_processors_num();
*/

/*
** on linux detecting number of processors on machine:
** #include <sys/sysinfo.h>
** and using:
**	{
**		return (sysconf(_SC_NPROCESSORS_ONLN));
**	}
*/

/*
** on win32 detecting number of processors on machine:
**	{
**		SYSTEM_INFO		sysinfo;
**
**		GetSystemInfo(&sysinfo);
**		return (sysinfo.dwNumberOfProcessors);
**	}
*/

int		ft_get_processors_num(void)
{
	int		nm[2];
	int		count;
	size_t	len;

	len = 4;
	nm[0] = CTL_HW;
	nm[1] = HW_AVAILCPU;
	sysctl(nm, 2, &count, &len, NULL, 0);
	if (count < 1)
	{
		nm[1] = HW_NCPU;
		sysctl(nm, 2, &count, &len, NULL, 0);
		if (count < 1)
			count = 1;
	}
	return (count);
}
