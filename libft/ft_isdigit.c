/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqueguin <mqueguin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 16:49:53 by tale-fau          #+#    #+#             */
/*   Updated: 2022/02/24 18:05:08 by mqueguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_is_digit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	ft_isdigit(char *str)
{
	int	i;

	i = -1;
	if (str[0] == '-' || str[0] == '+')
		i = 0;
	while (str[++i])
	{
		if ((!(str[i] >= '0' && str[i] <= '9')))
			return (0);
	}
	return (1);
}
