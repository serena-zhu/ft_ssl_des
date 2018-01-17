/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base64.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yazhu <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/15 17:18:40 by yazhu             #+#    #+#             */
/*   Updated: 2018/01/16 16:15:31 by yazhu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_des.h"

char g_b64[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K',
	'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V',
	'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f', 'g',
	'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r',
	's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '0', '1', '2',
	'3', '4', '5', '6', '7', '8', '9', '+', '/', '\0'};

static void		encryption(char *s, int fd_out, char *group)
{
	int i;
	int	j;
	int value;

	i = 0;
	while (s[i] != '\0')
	{
		j = 0;
		value = 0;
		ft_bzero(group, 5);
		while (s[i] != '\0' && j < 3)
			value += ft_power(256, 3 - (++j)) * s[i++];
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

static void		decryption(char *s, int fd_out, char *group, int i)
{
	int	j;
	int val_idx[2];
	int abort;

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
		ft_putstr_fd((!abort) ? group : "", fd_out);
	}
	ft_putstr_fd((!abort) ? "\n" : "", fd_out);
}

static void		processes(char *s, int fd_out, int encrypt)
{
	char	group[5];

	ft_bzero(group, sizeof(group));
	if (encrypt)
		encryption(s, fd_out, group);
	else
		decryption(s, fd_out, group, 0);
}

/*
** error [0] : unknown option provided && usuage error
** error [1] : missing file argument for -i or -o
** error [2] : usuage error
** error [3] : invalid file error
*/

static void		option_file_error(char **argv, int i, int error)
{
	if (error == 0)
	{
		ft_putstr("unknown option '");
		ft_putstr(argv[i]);
		ft_putstr("'\n");
	}
	if (error == 1)
	{
		ft_putstr("missing file argument for ");
		ft_putendl(argv[i - 1]);
	}
	if (error == 0 || error == 1 || error == 2)
	{
		ft_putstr("usage: enc -ciphername [-base64]\n");  //add to this?
		ft_putstr("-d              Decrypt the input data\n");
		ft_putstr("-e              Encrypt the input data (default)\n");
		ft_putstr("-i              Input file to read from (default stdin)\n");
		ft_putstr("-o              Output file to write to (default stdout)\n");
	}
	if (error == 3)
	{
		ft_putstr(argv[i]);
		ft_putstr(": No such file or directory\n");
	}
	exit(1);
}

static void		base64(int argc, char **argv, int i)
{
	int fd_in;
	int	fd_out;
	int	encrypt;

	fd_in = 0;
	fd_out = 1;
	encrypt = 1;
	while (i < argc && (ft_strcmp(argv[i], "-e") == 0
				|| ft_strcmp(argv[i], "-d") == 0))
		encrypt = (ft_strcmp(argv[i++], "-d") == 0) ? 0 : 1;
	if (i < argc && ft_strcmp(argv[i], "-i") == 0 && ++i)
	{
		(i >= argc) ? option_file_error(argv, i, 1) : 0;
		if ((fd_in = open(argv[i++], O_RDONLY)) < 0)
			(i - 1 < argc) ? option_file_error(argv, i - 1, 3) : exit(1);
	}
	if (i < argc && ft_strcmp(argv[i], "-o") == 0 && ++i)
	{
		(i >= argc) ? option_file_error(argv, i, 1) : 0;
		if ((fd_out = open(argv[i++], O_CREAT | O_TRUNC | O_WRONLY, 0666)) < 0)
			exit(1);
	}
	(i < argc) ? option_file_error(argv, i, 2 * (argv[i][0] == '-')) : 0;
	processes(read_data(fd_in), fd_out, encrypt);
}
