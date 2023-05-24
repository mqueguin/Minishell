/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tablen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tale-fau <tale-fau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/16 16:52:14 by tale-fau          #+#    #+#             */
/*   Updated: 2021/12/07 14:40:33 by tale-fau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
/* ATTENTION le cas ou le pipe est le premier arg n est pas gerer */

size_t	ft_tablen_pipe(char **s)
{
	size_t	i;

	i = 0;
	if (s == NULL)
		return (0);
	while (s[i])
	{
		if (s[i][0] == '|')
		{
			if (i == 0)
				return (0);
			return (i - 1);
		}
		i++;
	}
	return (i);
}

size_t	ft_tablen(char **s)
{
	size_t	i;

	i = 0;
	if (s == NULL)
		return (0);
	while (s[i])
		i++;
	return (i);
}
