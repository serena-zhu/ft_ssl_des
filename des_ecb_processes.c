/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_ecb_processes.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yazhu <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/23 10:52:33 by yazhu             #+#    #+#             */
/*   Updated: 2018/01/23 11:57:06 by yazhu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_des.h"

void		encrypt_b64_and_print(t_opt *opt)
{
	char *tmp;

	tmp = ft_strdup(opt->b64_s);
	ft_bzero(opt->b64_s, ft_strlen(opt->b64_s));
	b64_encrypt(tmp, opt, 0);
	ft_putstr_fd(opt->b64_s, opt->fd_out);
	free(tmp);
	free(opt->b64_s);
}

void		des_ecb_processes(unsigned long long s_blk, t_opt *opt, int padded)
{
	char	blk[9];
	int		j;

	ft_bzero(blk, 9);
	if (!opt->encrypt)
	{
		j = s_blk % 256;
		if (j > 0 && j <= 8)
			s_blk = (j == 8) ? 0 : s_blk / ft_power(256, j) * ft_power(256, j);
	}
	if (s_blk != 0)
	{
		j = 8;
		while (--j >= 0)
			blk[7 - j] = s_blk / ft_power(256, j) % 256;
		if (opt->encrypt && opt->base64)
		{
			join_b64_str(opt, blk);
			if (padded)
				encrypt_b64_and_print(opt);
		}
		else
			ft_putstr_fd(blk, opt->fd_out);
	}
}
