/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tale-fau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 18:15:29 by tale-fau          #+#    #+#             */
/*   Updated: 2021/06/02 16:16:45 by tale-fau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t	i;

	i = 0;
	if (!dest && !src)
		return (NULL);
	if (src < dest)
	{
		while (n > i)
		{
			((unsigned char *)dest)[n - 1] = ((unsigned char *)src)[n - 1];
			n--;
		}
	}
	else
	{
		while (i < n)
		{
			((unsigned char *)dest)[i] = ((unsigned char *)src)[i];
			i++;
		}
	}
	return (dest);
}
