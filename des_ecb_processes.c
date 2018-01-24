/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_ecb_processes.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yazhu <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/23 10:52:33 by yazhu             #+#    #+#             */
/*   Updated: 2018/01/23 22:26:10 by yazhu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_des.h"
#include <stdio.h> //delete me!!
/*
void		print_8_bytes(char *str, int fd_out)
{
	int i;

	i = 0;
	while (i++ < 8)
		ft_putchar_fd(str[i], fd_out);
}
*/
void		encrypt_b64_and_print(t_opt *opt)
{
	unsigned char *tmp;

//	printf("opt str is first %s\n", opt->b64_s);
//	tmp = strdup2(opt->b64_s);
//	tmp = strljoin(opt->b64_s, tmp, 0, 8 * opt->offset);
	tmp = strnew(8 * opt->offset);
	int j = 0;
	while (j < (8 * opt->offset))
	{
		tmp[j] = opt->b64_s[j];
		j++;
	}
	ft_bzero(opt->b64_s, 8 * (opt->offset));
//	printf("opt offset is %d\n", opt->offset);
//	printf("tmp is %s and opt->b64_s is %s\n", tmp, opt->b64_s);
//	printf("tmp is %s\n", tmp);
//	int i = 0;
//	while (i < 8)
//		printf("byte is %x\n", tmp[i++]);
	opt->len = 8 * opt->offset;
//	printf("len is %d and this shoudl be 8 %d\n", opt->len, opt->offset * 8);
	b64_encrypt(tmp, opt, 0);
	putstr_fd(opt->b64_s, opt->fd_out);
	opt->len = 0; //reset so it wont go back in the loop in encrypt_decrypt function
	free(tmp);
	free(opt->b64_s);
}

void		des_ecb_processes(unsigned long long s_blk, t_opt *opt, int padded)
{
	unsigned char	blk[9];
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
//		int k = 0;
//		while (k < 9)
//			printf("blk char is %c\n", blk[k++]);
		if (opt->encrypt && opt->base64)
		{
//			printf("opt->b64_s is %s, opt->len should be 0 %d, blk is %s\n", opt->b64_s, opt->len, blk);
//			printf("here\n");
			opt->b64_s = strljoin(opt->b64_s, blk, 8 * opt->offset++, 8);
//			int i = 0;
//			while (i < 8)
//				printf("byte is first %x\n", opt->b64_s[i++]);
//			printf("padded should be 5 %d\n", padded);
			if (padded)
				encrypt_b64_and_print(opt);
		}
		else
//			putnstr_fd(blk, opt->fd_out, 8);
			putstr_fd(blk, opt->fd_out);
	}
}
