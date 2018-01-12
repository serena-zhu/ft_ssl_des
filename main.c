/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yazhu <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/11 15:03:26 by yazhu             #+#    #+#             */
/*   Updated: 2018/01/11 19:22:24 by yazhu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_des.h"
#include <stdio.h> //delete me!!

long long 	ft_power(long long nbr, int power);

char base64_tab[64] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K',
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

void	encryption(char *s, int encrypt, char *i_file, char *o_file)
{
	(void)i_file;
	(void)o_file;
	int i;
	int	j;
	int value;
	char group[5];

	i = 0;
	j = 0;
	group[4] = '\0';
	if (encrypt)
	{
		while (s[i] != '\0')
		{
			j = 0;
			value = 0;
			while (j++ < 3 && s[i] != '\0')
				value += ft_power(256, 3 - j) * s[i++];
//				value = s[0] * 256 * 256 + s[1] * 256 + s[2];
			j = 4;
			while (j > 0)
			{
				if (value == 0)
					group[--j] = '=';
				else
					group[--j] = base64_tab[value % 64];
				value /= 64;
			}
			ft_putstr(group);
		}
	}
	else
	{

	}
}

void	base64(int argc, char **argv)
{
	int	i;
	int	encrypt;
	char *i_file;
	char *o_file;

	i = 2;
	encrypt = 1;
	i_file = NULL;
	o_file = NULL;
	while (i < argc && (ft_strcmp(argv[i], "-e") == 0 || !(encrypt = ft_strcmp(argv[i], "-d"))))
		i++;
	if (ft_strcmp(argv[i], "-i") == 0 && ++i)
		i_file = ft_strdup(argv[i++]);
	else if (ft_strcmp(argv[i], "-o") == 0 && ++i)
		o_file = ft_strdup(argv[i++]);
	//what if flag is provided but file name was not?
	//
	//string to (d)ecrypt is not provided as arg? but need to read in from stdout or file?
	if (i < argc)
		encryption(argv[i], encrypt, i_file, o_file);  
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
