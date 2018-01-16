/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base64.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yazhu <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/15 17:18:40 by yazhu             #+#    #+#             */
/*   Updated: 2018/01/15 18:12:41 by yazhu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_des.h"

char gbase64[65] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K',
					'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V',
					'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f', 'g',
					'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r',
					's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '0', '1', '2',
					'3','4', '5', '6', '7', '8', '9', '+', '/', '\0'};

void	encryption(char *s, int fd_out)
{
	int i;
	int	j;
	int value;
	char group[5];

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
			group[j] = (group[j] != '=') ? gbase64[value % 64] : group[j];
			value /= 64;
			j--;
		}
		ft_putstr_fd(group, fd_out);
		ft_putstr_fd((i != 0 && i % 48 == 0 && group[0] && s[i]) ? "\n" : "", fd_out);
	}
	ft_putstr_fd((group[0]) ? "\n" : "", fd_out);
}

void	decryption(char *s, int fd_out)
{
	int i;
	int	j;
	int value;
	char group[5];
	int index;
	int abort;

	i = 0;
	abort = 0;
	while (s[i] != '\0' && !abort && !(j = 0))
	{
		value = 0;
		ft_bzero(group, 5);
		while (s[i] != '\0' && j < 4 && !abort && !(index = 0))
		{
			i = (i != 0 && i % 64 == 0 && s[i] == '\n') ? i + 1 : i;
			while (s[i] != '=' && index < 64 && gbase64[index] != s[i])
				index++;
			abort = (index == 64) ? 1 : 0;
			value += ft_power(64, 4 - (++j)) * index;
			i++;
		}
		while (j-- >= 0)
		{
			group[j - 1] = value % 256;
			(ft_haschar(gbase64, value % 256)) ? value /= 256 : exit(1);
		}
		ft_putstr_fd((!abort) ? group : "", fd_out);
	}
	ft_putstr_fd((!abort) ? "\n" : "", fd_out);
}

/*
** error [0] : unknown option provided && usuage error
** error [1] : missing file argument for -i or -o
** error [2] : usuage error
** error [3] : invalid file error
*/

void	option_file_error(char **argv, int i, int error)
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
		ft_putendl(argv[i -1]);
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

void	base64(int argc, char **argv)
{
	int	i;
	int fd_in;
	int	fd_out;
	int	encrypt;

	i = 2;
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
	(encrypt) ? encryption(read_data(fd_in), fd_out) : decryption(read_data(fd_in), fd_out);
}
