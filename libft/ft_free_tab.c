/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_tab.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tale-fau <tale-fau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 18:37:28 by tale-fau          #+#    #+#             */
/*   Updated: 2022/02/22 23:08:17 by tale-fau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_free_tab(char **str)
{
	int	i;

	i = 0;
	if (str)
	{
		while (str[i])
		{
			if (str[i] != NULL)
				free(str[i]);
			i++;
		}
		free(str);
		str = NULL;
	}
	return (NULL);
}
