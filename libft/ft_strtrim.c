/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tale-fau <tale-fau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 20:39:29 by tale-fau          #+#    #+#             */
/*   Updated: 2021/06/02 16:22:40 by tale-fau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	find_set(const char *set, char s)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == s)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	len;
	size_t	i;

	i = 0;
	if (!s1)
		return (NULL);
	if (!set)
		return (ft_strdup(s1));
	while (s1[i] && find_set(set, s1[i]))
		i++;
	if (i >= ft_strlen(s1))
		return ((char *)ft_calloc(1, 1));
	start = i;
	i = ft_strlen(s1) - 1;
	while (find_set(set, s1[i]))
		i--;
	len = i - start + 1;
	return (ft_substr(s1, start, len));
}
