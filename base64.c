/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base64.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yazhu <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/15 17:18:40 by yazhu             #+#    #+#             */
/*   Updated: 2018/01/23 22:11:33 by yazhu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_des.h"
#include <stdio.h> //delete me!!
char g_b64[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K',
	'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V',
	'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f', 'g',
	'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r',
	's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '0', '1', '2',
	'3', '4', '5', '6', '7', '8', '9', '+', '/', '\0'};

void		join_b64_str(t_opt *opt, unsigned char *str)
{
	unsigned char *tmp;

	tmp = opt->b64_s;
	opt->b64_s = strljoin(opt->b64_s, str, 0, strlen2(str));
	free(tmp);
}

void		b64_encrypt(unsigned char *s, t_opt *opt, int j)
{
	int		i;
	int		value;
	unsigned char	group[4];

	i = 0;
	while (i < opt->len)
	{
		j = 0;
		value = 0;
		ft_bzero(group, 4);
		while (i < opt->len && j < 3)
			value += (ft_power(256, 3 - (++j)) * (unsigned char)s[i++]);
		while (j < 3)
			group[++j] = '=';
		while (j >= 0)
		{
			group[j] = (group[j] != '=') ? g_b64[value % 64] : group[j];
			value /= 64;
			j--;
		}
		join_b64_str(opt, group);
		(i != 0 && i % 48 == 0 && group[0] && s[i])
								? join_b64_str(opt, (unsigned char *)"\n") : 0;
	}
	(group[0]) ? join_b64_str(opt, (unsigned char *)"\n") : 0;
}

/*
** val_idx[0] : value
** val_idx[1] : index
*/

void		b64_decrypt(unsigned char *s, t_opt *opt, int i, int j)
{
	int		val_idx[2];
	int		abort;
	unsigned char	group[5];

	abort = 0;
	while (i < opt->len && !abort && !(j = 0))
	{
		val_idx[0] = 0;
		ft_bzero(group, 5);
		while (i < opt->len && j < 4 && !abort && !(val_idx[1] = 0))
		{
			i = (i != 0 && i % 64 == 0 && s[i] == '\n') ? i + 1 : i;
			while (s[i] != '=' && val_idx[1] < 64 && g_b64[val_idx[1]] != s[i])
				val_idx[1]++;
			abort = (++i && val_idx[1] == 64) ? 1 : 0;
//			printf("s[i] is %c and index is %d\n", s[i - 1], val_idx[1]);
//			printf("abort should be 0 %d and len is %d\n", abort, opt->len);
			val_idx[0] += ft_power(64, 4 - (++j)) * val_idx[1];
//			printf("val is %d\n", val_idx[0]);
		}
		while (j-- >= 0)
		{
			group[j - 1] = val_idx[0] % 256;
//			printf("char is %c\n", val_idx[0] % 256);
			val_idx[0] /= 256;
//			(ft_haschar(g_b64, val_idx[0] % 256)) ? val_idx[0] /= 256 : exit(1);
		}
		(!abort) ? join_b64_str(opt, group) : 0;
	}
	(!abort) ? join_b64_str(opt, (unsigned char *)"\n") : 0;
}

/*
** key not used for this cipher, but will not throw error if user provides one
*/

void		base64(int argc, char **argv)
{
	t_opt	opt;
	unsigned char	*s;

	initialize_opt(&opt, 0);
	populate_data(argc, argv, &opt);
	s = read_data(&opt);
	if (opt.encrypt)
		b64_encrypt(s, &opt, 0);
	else
		b64_decrypt(s, &opt, 0, 0);
	putstr_fd(opt.b64_s, opt.fd_out);
	free(opt.b64_s);
	free(s);
}
