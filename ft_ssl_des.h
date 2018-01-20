/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl_des.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yazhu <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/11 15:15:10 by yazhu             #+#    #+#             */
/*   Updated: 2018/01/19 21:57:16 by yazhu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_DES_H
# define FT_SSL_DES_H

# include "libft.h"
# include <fcntl.h>

char				*read_data(int fd);
long long			ft_power(long long nbr, int power);
int					ft_haschar(const char *str, const char c);
unsigned long long	permutate(unsigned long long in, int *permutation, int tab_size, int size);
//void				des_ecb_decrypt(char *text, char *key, int fd_out);
void				get_permutate_subkeys(char *key, unsigned long long *subkeys);
void				des_ecb(int argc, char **argv, int i);
void				encryption(char *s, int fd_out, char *group); //for base64, maybe rename?
//void				decryption(char *s, int fd_out, char *group, int i); //for base64, maybe rename?
void				base64(int argc, char **argv, int i);
int					main(int argc, char **argv);
#endif
