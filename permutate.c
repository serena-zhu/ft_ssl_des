/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   permutate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yazhu <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/18 17:29:49 by yazhu             #+#    #+#             */
/*   Updated: 2018/01/18 19:18:59 by yazhu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_des.h"

unsigned long long		permutate(unsigned long long in, int *permutation, int tab_size, int size)
{
	unsigned long long	out;
	int					i;

	out = 0;
	i = tab_size;
	while (i-- > 0)
	{
		if((in >> (size - permutation[i])) & 1)
			out = (unsigned long long)1 << (tab_size - 1 - i) | out;
	}
	return (out);
}
