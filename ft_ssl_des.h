/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl_des.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yazhu <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/11 15:15:10 by yazhu             #+#    #+#             */
/*   Updated: 2018/01/22 18:45:15 by yazhu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_DES_H
# define FT_SSL_DES_H

# include "libft.h"
# include <fcntl.h>

typedef struct		s_opt
{
	int				encrypt;
	int				base64;
	char			*b64_s;
//	int				nopad;
	int				fd_in;
	int				fd_out;
}					t_opt;

char				*read_data(int fd);
long long			ft_power(long long nbr, int power);
int					ft_haschar(const char *str, const char c);
unsigned long long	permutate(unsigned long long in, int *permutation,
													int tab_size, int size);
void				get_permutate_subkeys(char *key,
												unsigned long long *subkeys);
void				des_ecb(int argc, char **argv);
void				b64_encrypt(char *s, int fd_out, char *group); //for base64, maybe rename?
void				base64(int argc, char **argv);
void				errors(char **argv, int i, int error);
char				*populate_data(int argc, char **argv, char *key,
																t_opt *opt);
void				initialize_opt(t_opt *opt);
int					main(int argc, char **argv);
#endif
