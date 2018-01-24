/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strljoin.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yazhu <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/23 16:51:19 by yazhu             #+#    #+#             */
/*   Updated: 2018/01/23 21:10:24 by yazhu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_des.h"
#include <stdio.h> //delete me!!!
/*
** Modified version of ft_strjoin, offset is provided to preserve trailing '\0'
** between s1 and s2 as desired; the larger of offet or length of s1 is used.
** s2_len is the number of chars to be copied from s2, so that trailing '\0'
** can be included if desired or s2 can be truncated as desired
*/

unsigned char	*strljoin(unsigned char const *s1, unsigned char const *s2, size_t offset, size_t s2_len)
{
	size_t	len;
	size_t	s1_len;
	size_t	i;
	unsigned char	*str;

	if (s1 && s2)
	{
		i = 0;
		s1_len = strlen2(s1);
		offset = (offset < s1_len) ? s1_len : offset;
		len = (offset >= s1_len) ? offset + s2_len : s1_len + s2_len;
		str = (unsigned char *)malloc((len + 1) * sizeof(unsigned char));
//		printf("!!s1 is %s, s2 is %s, offset is %zu, len is %zu\n", s1, s2, offset, len);
		if (str)
		{
			ft_bzero(str, len + 1);
			strcpy2(str, s1);
			while (i < s2_len)
			{
				str[i + offset] = (unsigned char)s2[i];
//				printf("char is %d and this is copied %d\n", (unsigned char)s2[i], str[i + offset]);
				i++;
			}
			return (str);
		}
	}
	return (NULL);
}
