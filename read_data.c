/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yazhu <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/15 17:10:42 by yazhu             #+#    #+#             */
/*   Updated: 2018/01/23 09:57:07 by yazhu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_des.h"

char	*read_data(int fd)
{
	int		ret;
	char	buf[4096];
	char	*data;
	char	*tmp;

	ret = 0;
	ft_bzero(buf, sizeof(buf));
	data = ft_strnew(sizeof(buf));
	while ((ret = read(fd, buf, sizeof(buf) - 1)))
	{
		tmp = ft_strdup(data);
		data = ft_strjoin(tmp, buf);
		free(tmp);
		ft_bzero(buf, sizeof(buf));
	}
	if (fd > 0)
		close(fd);
	return (data);
}
