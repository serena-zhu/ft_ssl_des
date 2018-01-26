/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yazhu <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/28 15:25:13 by yazhu             #+#    #+#             */
/*   Updated: 2017/11/28 16:32:12 by yazhu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memalloc(size_t size)
{
	void	*tmp;
	size_t	i;

	i = 0;
	tmp = (void *)malloc(size * sizeof(*tmp));
	if (tmp)
	{
		while (i < size)
		{
			((char *)tmp)[i] = 0;
			i++;
		}
		return (tmp);
	}
	return (NULL);
}
