/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yazhu <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/11 15:03:26 by yazhu             #+#    #+#             */
/*   Updated: 2018/01/16 16:18:24 by yazhu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_des.h"
#include <stdio.h> //delete me!!

void	des_cbc(char **argv)
{
	(void)argv;
}

/*
** error [0] : unknown option provided && usuage error
** error [1] : missing file argument for -i or -o
** error [2] : usuage error
** error [3] : invalid file error
*/
/*
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

void	encryption(char *s, int encrypt, int fd_out)//, char *i_file, char *o_file)
{
	int i;
	int	j;
	int value;
	char group[5];
	int index;
	int abort;

	abort = 0;
	i = 0;
	j = 0;
	if (encrypt)
	{
		while (s[i] != '\0')
		{
			j = 0;
			value = 0;
			ft_bzero(group, 5);
			while (s[i] != '\0' && j < 3)
				value += ft_power(256, 3 - (++j)) * s[i++];
//				value = s[0] * 256 * 256 + s[1] * 256 + s[2];
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
	else
	{
		while (s[i] != '\0' && !abort)
		{
			j = 0;
			value = 0;
			ft_bzero(group, 5);
			while (s[i] != '\0' && j < 4 && !abort)
			{
				index = 0;
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
				value /= 256;
			}
			ft_putstr((!abort) ? group : "");
		}
		ft_putstr((!abort) ? "\n" : "");		
	}
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
*/
int		main(int argc, char **argv)
{
	if (argc == 1)
		ft_putstr("usage: ft_ssl command [command opts] [command args]\n");
	else
	{
		if (ft_strcmp(argv[1], "base64") == 0)
			base64(argc, argv, 2);
		else if (ft_strcmp(argv[1], "des") == 0)
			des(argc, argv);
		else if (ft_strcmp(argv[1], "des-cbc") == 0)
			des_cbc(argv);
		else
		{
			ft_putstr("ft_ssl: Error: '");
			ft_putstr(argv[1]);
			ft_putstr("' is an invalid command.\n\nStandard commands:\n\n");
			ft_putstr("Message Digest commmands:\n\nCipher commands:\nbase64\n");
			ft_putstr("des\ndes-ecb\ndes-cbc\n");
		}	
	}
	return (0);
}
