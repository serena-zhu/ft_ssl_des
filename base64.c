/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base64.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yazhu <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/15 17:18:40 by yazhu             #+#    #+#             */
/*   Updated: 2018/01/20 19:13:40 by yazhu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_des.h"

char g_b64[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K',
	'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V',
	'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f', 'g',
	'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r',
	's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '0', '1', '2',
	'3', '4', '5', '6', '7', '8', '9', '+', '/', '\0'};

void			b64_encrypt(char *s, int fd_out, char *group)
{
	int		i;
	int		j;
	int		value;

	i = 0;
	while (s[i] != '\0')
	{
		j = 0;
		value = 0;
		ft_bzero(group, sizeof(group));
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
		ft_putstr_fd(group, fd_out);
		ft_putstr_fd((i != 0 && i % 48 == 0 && group[0] && s[i])
				? "\n" : "", fd_out);
	}
	ft_putstr_fd((group[0]) ? "\n" : "", fd_out);
}

/*
** val_idx[0] : value
** val_idx[1] : index
*/

static void		b64_decrypt(char *s, int fd_out, char *group, int i)
{
	int	j;
	int val_idx[2];
	int abort;

	abort = 0;
	while (s[i] != '\0' && !abort && !(j = 0))
	{
		val_idx[0] = 0;
		ft_bzero(group, sizeof(group));
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
		ft_putstr_fd((!abort) ? group : "", fd_out);
	}
	ft_putstr_fd((!abort) ? "\n" : "", fd_out);
}

/*
** key not used for this cipher, but will not throw error if user provides one
*/

void			base64(int argc, char **argv)
{
	t_opt	opt;
	char	*s;
	char	*key;
	char	group[5];

	key = NULL;
	initialize_opt(&opt);
	key = populate_data(argc, argv, key, &opt);
	s = read_data(opt.fd_in);
	if (opt.encrypt)
		b64_encrypt(s, opt.fd_out, group);
	else
		b64_decrypt(s, opt.fd_out, group, 0);
}
