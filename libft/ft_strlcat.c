/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tale-fau <tale-fau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 16:51:33 by tale-fau          #+#    #+#             */
/*   Updated: 2021/01/07 22:10:19 by tale-fau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*str_ncat(char *dst, const char *src, size_t n)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (dst[i])
		i++;
	j = 0;
	while (src[j] && j < n)
	{
		dst[i + j] = src[j];
		j++;
	}
	dst[i + j] = '\0';
	return (dst);
}

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	max;
	size_t	s_dst;
	size_t	s_src;

	s_dst = ft_strlen((const char *)dst);
	s_src = ft_strlen(src);
	max = size - s_dst - 1;
	if (size <= s_dst)
		return (s_src + size);
	else
		str_ncat(dst, src, max);
	return (s_dst + s_src);
}
