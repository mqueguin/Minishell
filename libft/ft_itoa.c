/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tale-fau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/02 15:51:40 by tale-fau          #+#    #+#             */
/*   Updated: 2021/06/02 15:58:45 by tale-fau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	n_size(int n)
{
	int			i;
	long int	nb;

	i = 0;
	nb = n;
	if (nb < 0)
		nb = nb * -1;
	while (nb > 0)
	{
		nb = nb / 10;
		i++;
	}
	return (i);
}

void	loop(long int nb, char *ret, int size)
{
	while (nb > 0)
	{
		ret[size] = (nb % 10) + 48;
		nb = nb / 10;
		size--;
	}
}

char	*if_zero(char *ret)
{
	ret = (char *)malloc(sizeof(char) * 2);
	if (ret == NULL)
		return (NULL);
	ret[1] = '\0';
	ret[0] = '0';
	return (ret);
}

char	*ft_itoa(int n)
{
	int			sign;
	int			size;
	char		*ret;
	long int	nb;

	sign = 0;
	ret = NULL;
	nb = n;
	if (n == 0)
	{
		ret = if_zero(ret);
		return (ret);
	}
	if (n < 0)
		nb = nb * -1;
	size = n_size(n) + sign;
	ret = (char *)malloc(sizeof(char) * (size + 1));
	if (ret == NULL)
		return (NULL);
	ret[size] = '\0';
	size--;
	loop(nb, ret, size);
	return (ret);
}
