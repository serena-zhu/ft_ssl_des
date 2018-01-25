/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yazhu <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/15 17:10:42 by yazhu             #+#    #+#             */
/*   Updated: 2018/01/25 12:48:16 by yazhu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_des.h"

unsigned char	*read_data(t_opt *opt)
{
	int				ret;
	int				read_count;
	unsigned char	buf[BUFF_SIZE + 1];
	unsigned char	*data;
	unsigned char	*tmp;

	ret = 0;
	ft_bzero(buf, BUFF_SIZE + 1);
	read_count = 0;
	while ((ret = read(opt->fd_in, buf, BUFF_SIZE)))
	{
		tmp = data;
		data = (unsigned char *)malloc(BUFF_SIZE * ++read_count
													* sizeof(unsigned char));
		if (read_count > 1)
		{
			ft_memcpy(data, tmp, BUFF_SIZE * read_count);
			free(tmp);
		}
		ft_memcpy(data + BUFF_SIZE * (read_count - 1), buf, ret);
		ft_bzero(buf, BUFF_SIZE);
		opt->len += ret;
	}
	(opt->fd_in > 0) ? close(opt->fd_in) : 0;
	return (data);
}
