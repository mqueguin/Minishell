/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqueguin <mqueguin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 20:27:05 by tale-fau          #+#    #+#             */
/*   Updated: 2022/02/27 22:19:11 by mqueguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_null(char *s1, char *s2, int j)
{
	char	*ret;
	size_t	len;
	int		i;

	if (!s2 && s1)
		return (s1);
	else if (!s1 && s2)
		return (s2);
	len = (ft_strlen(s1) + ft_strlen(s2)) + 1;
	ret = (char *)malloc(sizeof(char) * len + 1);
	if (ret == NULL)
		return (NULL);
	i = 0;
	while (s1[i])
		ret[j++] = s1[i++];
	i = 0;
	while (s2[i])
	{
		ret[j] = s2[i];
		i++;
		j++;
	}
	ret[j] = '\0';
	return (ret);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ret;
	size_t	len;
	int		i;
	int		j;

	if (!s1 || !s2)
		return (NULL);
	len = (ft_strlen(s1) + ft_strlen(s2)) + 1;
	ret = ft_calloc(1, len);
	if (ret == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i])
		ret[j++] = s1[i++];
	i = 0;
	while (s2[i])
	{
		ret[j] = s2[i];
		i++;
		j++;
	}
	ret[j] = '\0';
	return (ret);
}
