/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp_check_len.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqueguin <mqueguin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 17:52:43 by mqueguin          #+#    #+#             */
/*   Updated: 2022/02/10 18:04:09 by mqueguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp_check_len(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (ft_strlen(s1) != ft_strlen(s2))
		return (-1);
	if (n == 0)
		return (0);
	while (s1[i] == s2[i] && s1[i] && s2[i] && i < n)
		i++;
	if (i == n && n > 0)
		i--;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
