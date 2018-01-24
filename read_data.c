/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yazhu <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/15 17:10:42 by yazhu             #+#    #+#             */
/*   Updated: 2018/01/23 20:52:21 by yazhu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_des.h"

unsigned char	*read_data(t_opt *opt)
{
	int		ret;
	int		read_count;
	unsigned char	buf[BUFF_SIZE + 1];
	unsigned char	*data;
	unsigned char	*tmp;

	ret = 0;
	ft_bzero(buf, BUFF_SIZE + 1);
	data = strnew(BUFF_SIZE + 1);
	read_count = 0;
	while ((ret = read(opt->fd_in, buf, BUFF_SIZE)))
	{
		tmp = strdup2(data);
		data = strljoin(tmp, buf, (size_t)(BUFF_SIZE * read_count), ret);
		read_count++;
		opt->len += ret;
		free(tmp);
		ft_bzero(buf, BUFF_SIZE);
	}
	if (opt->fd_in > 0)
		close(opt->fd_in);
	return (data);
}
