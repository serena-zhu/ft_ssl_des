/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yazhu <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/11 15:03:26 by yazhu             #+#    #+#             */
/*   Updated: 2018/01/15 14:34:17 by yazhu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_des.h"
#include <stdio.h> //delete me!!

long long 	ft_power(long long nbr, int power);

char gbase64[64] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K',
					'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V',
					'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f', 'g',
					'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r',
					's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '0', '1', '2',
					'3','4', '5', '6', '7', '8', '9', '+', '/'};


void	des(char **argv)
{
	(void)argv;
}

void	des_cbc(char **argv)
{
	(void)argv;
}

void	option_error(char *s)
{
	ft_putstr("unknown option '");
	ft_putstr(s);
	ft_putstr("'\n");
	ft_putstr("usage: enc -ciphername [-base64]\n");  //add to this?
	ft_putstr("-d                Decrypt the input data\n");
	ft_putstr("-e                Encrypt the input data (default)\n");
	ft_putstr("-i                Input file to read from (default stdin)\n");
	ft_putstr("-o                Output file to write to (default stdout)\n");
}

void	encryption(char *s, int encrypt)//, char *i_file, char *o_file)
{
//	(void)i_file;
//	(void)o_file;
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
			ft_putstr(group);
			ft_putstr((i != 0 && i % 48 == 0 && group[0] && s[i]) ? "\n" : "");
		}
		ft_putstr((group[0]) ? "\n" : "");
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

char	*read_data(int fd)
{
	int		ret;
	char	buf[4096];
	char	*data;
	char	*tmp;

	ret = 0;
	
	ft_bzero(buf, sizeof(buf));
	data = ft_strnew(sizeof(buf));
	while ((ret = read(fd, buf, sizeof(buf) - 1)))
	{
		tmp = ft_strdup(data);
		data = ft_strjoin(tmp, buf);
		free(tmp);
		ft_bzero(buf, sizeof(buf));
	}
	if (fd > 0)
		close(fd);
	return (data);
}

void	base64(int argc, char **argv)
{
	int	i;
	int fd;
	int	encrypt;
	char *o_file;

	i = 2;
	fd = 0;
	encrypt = 1;
	o_file = NULL;
	while (i < argc && (ft_strcmp(argv[i], "-e") == 0 || ft_strcmp(argv[i], "-d") == 0))
	{
		encrypt = (ft_strcmp(argv[i], "-d") == 0) ? 0 : encrypt;
		i++;
	}
	if (i < argc && ft_strcmp(argv[i], "-i") == 0 && ++i)
	{
		fd = open(argv[i], O_RDONLY);
		if (fd < 0)
		{
			if (i < argc)
			{
				ft_putstr(argv[i]);
				ft_putendl(": No such file or directory");
			}
			else
				ft_putstr("error\n");  //print supporting functions/options message
			return ;
		}
	}
	else if (i < argc && ft_strcmp(argv[i], "-o") == 0 && ++i)
		o_file = ft_strdup(argv[i++]);
	//what if flag is provided but file name was not?
	//
	//string to (d)ecrypt is not provided as arg? but need to read in from stdout or file?
//	read_data(fd);

	encryption(read_data(fd), encrypt);
//	if (i < argc)
//		encryption(argv[i], encrypt, i_file, o_file);  
}

int		main(int argc, char **argv)
{
	if (argc == 1)
		ft_putstr("usage: ft_ssl command [command opts] [command args]\n");
	else
	{
		if (ft_strcmp(argv[1], "base64") == 0)
			base64(argc, argv);
		else if (ft_strcmp(argv[1], "des") == 0)
			des(argv);
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
