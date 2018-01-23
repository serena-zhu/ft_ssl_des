/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base64.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yazhu <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/15 17:18:40 by yazhu             #+#    #+#             */
/*   Updated: 2018/01/23 11:07:49 by yazhu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_des.h"

char g_b64[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K',
	'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V',
	'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f', 'g',
	'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r',
	's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '0', '1', '2',
	'3', '4', '5', '6', '7', '8', '9', '+', '/', '\0'};

void		join_b64_str(t_opt *opt, char *str)
{
	char *tmp;

	tmp = opt->b64_s;
	opt->b64_s = ft_strjoin(opt->b64_s, str);
	free(tmp);
}

void		b64_encrypt(char *s, t_opt *opt, int j)
{
	int		i;
	int		value;
	char	group[4];

	i = 0;
	while (s[i] != '\0')
	{
		j = 0;
		value = 0;
		ft_bzero(group, 4);
		while (s[i] != '\0' && j < 3)
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
											? join_b64_str(opt, "\n") : 0;
	}
	(group[0]) ? join_b64_str(opt, "\n") : 0;
}

/*
** val_idx[0] : value
** val_idx[1] : index
*/

void		b64_decrypt(char *s, t_opt *opt, int i, int j)
{
	int		val_idx[2];
	int		abort;
	char	group[5];

	abort = 0;
	while (s[i] != '\0' && !abort && !(j = 0))
	{
		val_idx[0] = 0;
		ft_bzero(group, 5);
		while (s[i] != '\0' && j < 4 && !abort && !(val_idx[1] = 0))
		{
			i = (i != 0 && i % 64 == 0 && s[i] == '\n') ? i + 1 : i;
			while (s[i] != '=' && val_idx[1] < 64 && g_b64[val_idx[1]] != s[i])
				val_idx[1]++;
			abort = (++i && val_idx[1] == 64) ? 1 : 0;
			val_idx[0] += ft_power(64, 4 - (++j)) * val_idx[1];
		}
		while (j-- >= 0)
		{
			group[j - 1] = val_idx[0] % 256;
			(ft_haschar(g_b64, val_idx[0] % 256)) ? val_idx[0] /= 256 : exit(1);
		}
		(!abort) ? join_b64_str(opt, group) : 0;
	}
	(!abort) ? join_b64_str(opt, "\n") : 0;
}

/*
** key not used for this cipher, but will not throw error if user provides one
*/

void		base64(int argc, char **argv)
{
	t_opt	opt;
	char	*s;
	char	*key;

	key = NULL;
	initialize_opt(&opt);
	key = populate_data(argc, argv, key, &opt);
	s = read_data(opt.fd_in);
	if (opt.encrypt)
		b64_encrypt(s, &opt, 0);
	else
		b64_decrypt(s, &opt, 0, 0);
	ft_putstr_fd(opt.b64_s, opt.fd_out);
	free(opt.b64_s);
	free(s);
}
