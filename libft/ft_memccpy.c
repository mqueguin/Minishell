/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tale-fau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/04 16:59:36 by tale-fau          #+#    #+#             */
/*   Updated: 2020/12/09 19:14:42 by tale-fau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char		*t_dst;
	const unsigned char	*t_src;
	size_t				i;

	t_dst = dst;
	t_src = src;
	i = 0;
	while (i < n)
	{
		t_dst[i] = t_src[i];
		if (t_dst[i] == (unsigned char)c)
			return ((void *)&t_dst[i + 1]);
		i++;
	}
	return (0);
}
