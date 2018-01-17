/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl_des.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yazhu <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/11 15:15:10 by yazhu             #+#    #+#             */
/*   Updated: 2018/01/16 15:32:53 by yazhu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_DES_H
# define FT_SSL_DES_H

# include "libft.h"
# include <fcntl.h>

char		*read_data(int fd);
long long	ft_power(long long nbr, int power);
int			ft_haschar(const char *str, const char c);
void		base64(int argc, char **argv, int i);
int			main(int argc, char **argv);
#endif
