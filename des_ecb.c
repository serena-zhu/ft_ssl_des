/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_ecb.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yazhu <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/18 11:39:01 by yazhu             #+#    #+#             */
/*   Updated: 2018/01/22 19:36:01 by yazhu            ###   ########.fr       */
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

int		g_sbx[32][16] = {{14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7},
	{0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8},
	{4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0},
	{15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13},
	{15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10},
	{3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5},
	{0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6, 9, 3, 2, 15},
	{13, 8, 10, 1, 3, 15, 4, 2, 11, 6, 7, 12, 0, 5, 14, 9},
	{10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8},
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

int		g_p[] = {16, 7, 20, 21,
	29, 12, 28, 17,
	1, 15, 23, 26,
	5, 18, 31, 10,
	2, 8, 24, 14,
	32, 27, 3, 9,
	19, 13, 30, 6,
	22, 11, 4, 25};

int		g_finalp[] = {40, 8, 48, 16, 56, 24, 64, 32,
	39, 7, 47, 15, 55, 23, 63, 31,
	38, 6, 46, 14, 54, 22, 62, 30,
	37, 5, 45, 13, 53, 21, 61, 29,
	36, 4, 44, 12, 52, 20, 60, 28,
	35, 3, 43, 11, 51, 19, 59, 27,
	34, 2, 42, 10, 50, 18, 58, 26,
	33, 1, 41, 9, 49, 17, 57, 25};

char g_b64_dup[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K',
	'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V',
	'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f', 'g',
	'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r',
	's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '0', '1', '2',
	'3', '4', '5', '6', '7', '8', '9', '+', '/', '\0'};

static unsigned long long		encode(unsigned long long l,
					unsigned long long r, unsigned long long *subkeys, int i)
{
	unsigned long long	tmp_l;
	unsigned long long	tmp_box;
	unsigned long long	tmp_subkey;
	int					row_col[2];
	int					j;

	while (i++ < 16)
	{
		tmp_l = l;
		l = r;
		r = permutate(r, g_e, 48, 32);
		tmp_subkey = subkeys[i - 1] ^ r;
		j = 8;
		tmp_box = 0;
		while (--j >= 0)
		{
			row_col[1] = (tmp_subkey % 64) / 2 % 16;
			row_col[0] = (tmp_subkey % 64) / 32 * 2 + (tmp_subkey % 64) % 2;
			tmp_box += g_sbx[row_col[0] + j * 4][row_col[1]]
						* ft_power(16, 7 - j);
			tmp_subkey /= 64;
		}
		r = permutate(tmp_box, g_p, 32, 32) ^ tmp_l;
	}
	return (permutate(r * 4294967296 + l, g_finalp, 64, 64));
}

static unsigned long long		decode(unsigned long long l,
					unsigned long long r, unsigned long long *subkeys, int i)
{
	unsigned long long	tmp_r;
	unsigned long long	tmp_box;
	unsigned long long	tmp_subkey;
	int					row_col[2];
	int					j;

	while (--i >= 0)
	{
		tmp_r = r;
		r = l;
		l = permutate(l, g_e, 48, 32);
		tmp_subkey = subkeys[i] ^ l;
		j = 8;
		tmp_box = 0;
		while (--j >= 0)
		{
			row_col[1] = (tmp_subkey % 64) / 2 % 16;
			row_col[0] = (tmp_subkey % 64) / 32 * 2 + (tmp_subkey % 64) % 2;
			tmp_box += g_sbx[row_col[0] + j * 4][row_col[1]]
						* ft_power(16, 7 - j);
			tmp_subkey /= 64;
		}
		l = permutate(tmp_box, g_p, 32, 32) ^ tmp_r;
	}
	return (permutate(l * 4294967296 + r, g_finalp, 64, 64));
}

void							process_text(unsigned long long s_blk, t_opt *opt, int padded)
{
	char	blk[9];
	char	group[5];
	int		j;
//	int		padding;

	ft_bzero(blk, sizeof(blk));
	printf("s_blk is %llu\n", s_blk);
	if (!opt->encrypt)
	{
		j = s_blk % 256;
		printf("here, j is %d, ft_power(256, 8) is %lld\n", j, (unsigned long long)ft_power(256, 8));
		if (j > 0 && j <= 8)
		{
//			if (ft_power(256, j) == 0) //need to figure out why 258^8 is 0 -- maybe change ft_power to unsigned long long
//				s_blk = 0;
			if (j == 8)
				s_blk = 0; 
			else
				s_blk = s_blk / ft_power(256, j) * ft_power(256, j);
		}
		printf("s_blk is now 2 %llu\n", s_blk);
/*		padding = s_blk % 256;
//		printf("padding is %d and s_blk is %llu\n", padding, s_blk);
		if (padding >= 0 && padding <= 8 && (j = 1))
		{
			while ((s_blk / ft_power(256, j + 1) % 256) == padding)
				j++;
			printf("j is %d\n", j);
			if (j == padding - 1 && j > 0 && j <= 8)
				s_blk = s_blk / ft_power(256, j + 1) * ft_power(256, j + 1);
		}
*/	}
	if (s_blk != 0)
	{
		printf("s_blk is now %llu\n", s_blk);
		j = 8;
		while (--j >= 0)
			blk[7 - j] = s_blk / ft_power(256, j) % 256;
		if (opt->encrypt && opt->base64) //what about decrypt with -a flag?
		{
			opt->b64_s = ft_strjoin(opt->b64_s, blk);	
			if (padded)	
				b64_encrypt(opt->b64_s, opt->fd_out, group);
		}
		else
			ft_putstr_fd(blk, opt->fd_out);
	}
}

static void						encrypt_decrypt(char *text, char *key, t_opt opt)
{
	unsigned long long	subkeys[16];
	unsigned long long	s_blk;
	int					i;
	int					j;
	int					padded;

	i = 0;
	padded = 0;
	get_permutate_subkeys(key, subkeys);
	while (text[i] != '\0' || (opt.encrypt && padded == 0)) //is this okay?
	{
		j = 0;
		s_blk = 0;
		while (text[i] != '\0' && j++ < 8)
		{
			s_blk = s_blk * 256 + (unsigned char)text[i++];
			printf("text[i] is %x\n", text[i - 1]);
		}
		if (text[i] == '\0' && j < 8)
		{
			padded = 8 - j;
			while (j++ < 8)
				s_blk = s_blk * 256 + padded;
		}
		s_blk = permutate(s_blk, g_ip, 64, 64);
		if (opt.encrypt)
			s_blk = encode(s_blk / 4294967296, s_blk % 4294967296, subkeys, 0); //2^32 = 4294967296
		else
			s_blk = decode(s_blk % 4294967296, s_blk / 4294967296, subkeys, 16);
		process_text(s_blk, &opt, padded);
		printf("i is %d and text[i] is %c and this should be true %d\n", i, text[i], text[i] == '\0');
	}
}

static char		*decrypt_b64(char *s, t_opt *opt)
{
	int i;
	int	j;
	int val_idx[2];
	int abort;
	char group[5];

	i = 0;
	abort = 0;
	while (s[i] != '\0' && !abort && !(j = 0))
	{
		val_idx[0] = 0;
		ft_bzero(group, sizeof(group));
		while (s[i] != '\0' && j < 4 && !abort && !(val_idx[1] = 0))
		{
			i = (i != 0 && i % 64 == 0 && s[i] == '\n') ? i + 1 : i;
			while (s[i] != '=' && val_idx[1] < 64 && g_b64_dup[val_idx[1]] != s[i])
				val_idx[1]++;
			abort = (++i && val_idx[1] == 64) ? 1 : 0;
			val_idx[0] += ft_power(64, 4 - (++j)) * val_idx[1];
		}
		while (j-- >= 0)
		{
			group[j - 1] = val_idx[0] % 256;
			(ft_haschar(g_b64_dup, val_idx[0] % 256)) ? val_idx[0] /= 256 : exit(1);
		}
//		ft_putstr_fd((!abort) ? group : "", fd_out);
		opt->b64_s = (!abort) ? ft_strjoin(opt->b64_s, group) : NULL;
	}
//	ft_putstr_fd((!abort) ? "\n" : "", fd_out);
	if (!(opt->b64_s))
		exit(1);
	return (opt->b64_s);
}


//need to check for leaks!!!

void							des_ecb(int argc, char **argv)
{
	char	*key;
	char	*text;
	t_opt	opt;

	key = NULL;
	initialize_opt(&opt);
	if (argc <= 2)
		key = getpass("enter des key in hex: ");
	key = populate_data(argc, argv, key, &opt); //what if key is not the right length?!!
	text = read_data(opt.fd_in);
	if (opt.base64 && !opt.encrypt)
		text = decrypt_b64(text, &opt);
	//still need -a and flags
	encrypt_decrypt(text, key, opt);
}
