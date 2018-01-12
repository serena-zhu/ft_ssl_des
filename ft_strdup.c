/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yazhu <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/01 21:46:39 by yazhu             #+#    #+#             */
/*   Updated: 2017/11/30 16:36:03 by yazhu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	int		len;
	char	*ptr;

	len = 0;
	while (s1[len] != '\0')
	{
		len++;
	}
	ptr = (char *)malloc((len + 1) * sizeof(*ptr));
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
