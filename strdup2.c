/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strdup2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yazhu <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/01 21:46:39 by yazhu             #+#    #+#             */
/*   Updated: 2018/01/23 20:24:43 by yazhu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

unsigned char	*strdup2(const unsigned char *s1)
{
	int		len;
	unsigned char	*ptr;

	len = 0;
	while (s1[len] != '\0')
	{
		len++;
	}
	ptr = (unsigned char *)malloc((len + 1) * sizeof(*ptr));
	if (ptr)
	{
		len = 0;
		while (s1[len] != '\0')
		{
			ptr[len] = s1[len];
			len++;
		}
		ptr[len] = '\0';
		return (ptr);
	}
	return (NULL);
}
