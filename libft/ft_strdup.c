/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqueguin <mqueguin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 17:13:39 by tale-fau          #+#    #+#             */
/*   Updated: 2022/02/26 00:39:47 by mqueguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*ret;
	int		len;
	int		i;

	i = 0;
	ret = NULL;
	len = 0;
	if (!s)
		return (NULL);
	len = ft_strlen(s);
	ret = (char *)malloc(sizeof(char) * len + 1);
	if (ret == NULL)
		return (NULL);
	ft_bzero((void *)ret, len + 1);
	while (s[i])
	{
		ret[i] = s[i];
		i++;
	}
	ret[i] = '\0';
	return (ret);
}
