/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putnstr_fd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yazhu <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/23 19:04:15 by yazhu             #+#    #+#             */
/*   Updated: 2018/01/24 23:11:18 by yazhu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_des.h"

/*
**	Modified version of ft_putstr_fd where number of bytes to be printed is
**  specified so that '\0' in between or at the end can be printed as desired
*/

void	putnstr_fd(unsigned char const *s, int fd, int len)
{
	int i;

	if (s)
	{
		i = 0;
		while (i < len)
			write(fd, &s[i++], 1);
	}
}
