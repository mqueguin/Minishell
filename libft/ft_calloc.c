/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tale-fau <tale-fau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/02 15:48:45 by tale-fau          #+#    #+#             */
/*   Updated: 2022/02/02 17:24:32 by tale-fau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ret;

	if (nmemb == 0 || size == 0)
	{
		nmemb = 1;
		size = 1;
	}
	ret = malloc(size * nmemb);
	if (ret == NULL)
		return (NULL);
	ft_bzero(ret, nmemb * size);
	return (ret);
}
