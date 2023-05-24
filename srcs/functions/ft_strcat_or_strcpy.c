/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat_or_strcpy.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tale-fau <tale-fau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/30 11:19:02 by mqueguin          #+#    #+#             */
/*   Updated: 2022/02/24 18:20:06 by tale-fau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strcpy(char *dst, char *src)
{
	while (*src)
		*dst++ = *src++;
	*dst = '\0';
	return (dst);
}

char	*ft_strcat_true(char *dst, char *src)
{
	int	i;
	int	j;

	i = 0;
	if (dst == NULL || dst[0] == '\0')
		dst = ft_strcpy(dst, src);
	while (dst[i])
		i++;
	j = 0;
	while (src[j])
		dst[i++] = src[j++];
	return (dst);
}
