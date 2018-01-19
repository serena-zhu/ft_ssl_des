/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_ecb.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yazhu <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/18 11:39:01 by yazhu             #+#    #+#             */
/*   Updated: 2018/01/18 19:51:24 by yazhu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_des.h"
#include <stdio.h> //delete me!!!

int		g_ip[] = {58, 50, 42, 34, 26, 18, 10, 2,
				60, 52, 44, 36, 28, 20, 12, 4,
				 62, 54, 46, 38, 30, 22, 14, 6,
				 64, 56, 48, 40, 32, 24, 16, 8,
				 57, 49, 41, 33, 25, 17, 9, 1,
				 59, 51, 43, 35, 27, 19, 11, 3,
				 61, 53, 45, 37, 29, 21, 13, 5,
				 63, 55, 47, 39, 31, 23, 15, 7};

int		g_e[] = {32, 1, 2, 3, 4, 5,
				4, 5, 6, 7, 8, 9,
				8, 9, 10, 11, 12, 13,
				12, 13, 14, 15, 16, 17,
				16, 17, 18, 19, 20, 21,
				20, 21, 22, 23, 24, 25,
				24, 25, 26, 27, 28, 29,
				28, 29, 30, 31, 32, 1};

int		g_sbox[32][16] = {{14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7},
					{0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8},
					{4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0},
					{15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13},
					{15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10},
					{3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5},
					{0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6, 9, 3, 2, 15},
					{13, 8, 10, 1, 3, 15, 4, 2, 11, 6, 7, 12, 0, 5, 14, 9},
					{10, 0, 19, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8},
					{13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 15, 1},
					{13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12, 5, 10, 14, 7},
					{1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2, 12},
					{7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 8, 5, 11, 12, 4, 15},
					{13, 8, 11, 5, 6, 15, 0, 3, 4, 7, 2, 12, 1, 10, 14, 9},
					{10, 6, 9, 0, 12, 11, 7, 13, 15, 1, 3, 14, 5, 2, 8, 4},
					{3, 15, 0, 6, 10, 1, 13, 8, 9, 4, 5, 11, 12, 7, 2, 14},
					{2, 12, 4, 1, 7, 10, 11, 6, 8, 5, 3, 15, 13, 0, 14, 9},
					{14, 11, 2, 12, 4, 7, 13, 1, 5, 0, 15, 10, 3, 9, 8, 6},
					{4, 2, 1, 11, 10, 13, 7, 8, 15, 9, 12, 5, 6, 3, 0, 14},
					{11, 8, 12, 7, 1, 14, 2, 13, 6, 15, 0, 9, 10, 4, 5, 3},
					{12, 1, 10, 15, 9, 2, 6, 8, 0, 13, 3, 4, 14, 7, 5, 11},
					{10, 15, 4, 2, 7, 12, 9, 5, 6, 1, 13, 14, 0, 11, 3, 8},
					{9, 14, 15, 5, 2, 8, 12, 3, 7, 0, 4, 10, 1, 13, 11, 6},
					{4, 3, 2, 12, 9, 5, 15, 10, 11, 14, 1, 7, 6, 0, 8, 13},
					{4, 11, 2, 14, 15, 0, 8, 13, 3, 12, 9, 7, 5, 10, 6, 1},
					{13, 0, 11, 7, 4, 9, 1, 10, 14, 3, 5, 12, 2, 15, 8, 6},
					{1, 4, 11, 13, 12, 3, 7, 14, 10, 15, 6, 8, 0, 5, 9, 2},
					{6, 11, 13, 8, 1, 4, 10, 7, 9, 5, 0, 15, 14, 2, 3, 12},
					{13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 3, 14, 5, 0, 12, 7},
					{1, 15, 13, 8, 10, 3, 7, 4, 12, 5, 6, 11, 0, 14, 9, 2},
					{7, 11, 4, 1, 9, 12, 14, 2, 0, 6, 10, 13, 15, 3, 5, 8},
					{2, 1, 14, 7, 4, 10, 8, 13, 15, 12, 9, 0, 3, 5, 6, 11}};

void	encryption(char *text, char *key, int fd_out, int encrypt)
{
	(void)fd_out;
	(void)encrypt;
	unsigned long long	subkeys[16];
	unsigned long long	s;
	unsigned long long	l;
	unsigned long long	r;
	unsigned long long	tmp_l;
	unsigned long long	tmp_box;
	int					col;
	int					row;
	int					i;
	int					j;

	i = 0;
	s = 0;
	get_permutate_subkeys(key, subkeys);
	//need outer loop to process full message, right now only works with first 8 bytes
	while (text[i] != '\0' && i < 8)
	{
		s = s * 256 + (unsigned char)text[i]; //2^8 = 256
//		printf("text[i] is %u and s is %llu\n", (unsigned char)text[i], s);
		i++;
	}
	while (i++ < 8)
		s *= 256;
	s = permutate(s, g_ip, 64, 64);
	l = s / 4294967296; //2^32 = 4294967296
	r = s % 4294967296;
	printf("s is %llu, l is  %llu, r is %llu\n", s, l, r);
	i = 0;
	while (i < 16)
		printf("subkey is %llu\n", subkeys[i++]);
	tmp_l = l;
	l = r;
	r = permutate(r, g_e, 48, 32);
	printf("r is now %llu\n", r);
	subkeys[0] = subkeys[0] ^ r;
	printf("the first subkey is now %llu\n", subkeys[0]);
	i = 0;
	j = 0;
	tmp_box = 0;
	while (i < 8)  //left off here!!!
	{
		printf("subkey mod 64 is %llu\n", subkeys[0] % 64);
		col = (subkeys[0] % 64)	/ 2 % 16;
		row = (subkeys[0] % 64) / 16 + (subkeys[0] % 64) % 2;
		printf("tmp_box is %llu and about to add %lld\n", tmp_box, g_sbox[row + j * 4][col] * ft_power(16, i));
		tmp_box = tmp_box + g_sbox[row + j * 4][col] * ft_power(16, i);
		printf("row is %d col is %d and g_sbox there is %d\n", row, col, g_sbox[row + j * 4][col]);
		subkeys[0] /= 64;
		i++;
	}
	subkeys[0] = tmp_box;
	printf("subkeys[0] after s box is now %llu\n", subkeys[0]);
}

void	option_file_error(char **argv, int i, int error)
{
	if (error == 1)
	{
		ft_putstr("missing key argument for ");
		ft_putendl(argv[i - 1]);
	}
	if (error == 1)
	{
		ft_putstr("usage: enc -ciphername [-base64]\n");  //add to this?
		ft_putstr("-d              Decrypt the input data\n");
		ft_putstr("-e              Encrypt the input data (default)\n");
		ft_putstr("-i              Input file to read from (default stdin)\n");
		ft_putstr("-o              Output file to write to (default stdout)\n");	
	}
}

void	des_ecb(int argc, char **argv, int i)
{
	int fd_in;
	int	fd_out;
	int	encrypt;
	char *key;
	char *text;

	fd_in = 0;
	fd_out = 1;
	encrypt = 1;
	text = read_data(0);
/*	if (i >= argc)
	{
		ft_putstr("enter des key in hex: ");
		key = read_data(0);
	}
*/	while (i < argc && (ft_strcmp(argv[i], "-e") == 0 || ft_strcmp(argv[i], "-d") == 0))
		encrypt = (ft_strcmp(argv[i++], "-d") == 0) ? 0 : 1;
	if (i < argc && ft_strcmp(argv[i], "-k") == 0)
		(++i < argc) ? key = argv[i] : option_file_error(argv, i, 1);
	while (i < argc && (ft_strcmp(argv[i], "-e") == 0 || ft_strcmp(argv[i], "-d") == 0))
		encrypt = (ft_strcmp(argv[i++], "-d") == 0) ? 0 : 1;
// -a, -i, -o flags (can be before -k flag as well?)
	encryption(text, key, fd_out, encrypt);
}
