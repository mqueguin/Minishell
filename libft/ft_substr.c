/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tale-fau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 19:43:19 by tale-fau          #+#    #+#             */
/*   Updated: 2021/06/02 16:23:59 by tale-fau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char				*ret;
	unsigned int		i;
	unsigned int		j;

	ret = NULL;
	if (!s)
		return (NULL);
	if (start > ft_strlen(s))
		return (ft_calloc(1, sizeof(char)));
	ret = (char *)malloc(sizeof(char) * (len + 1));
	if (ret == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (i < start)
		i++;
	while (j < len)
	{
		ret[j] = s[i + j];
		j++;
	}
	ret[j] = '\0';
	return (ret);
}
