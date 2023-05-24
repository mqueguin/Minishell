/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tale-fau <tale-fau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 20:59:17 by tale-fau          #+#    #+#             */
/*   Updated: 2022/02/24 21:07:13 by tale-fau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*malloc_and_return(int len)
{
	char	*ret;

	ret = NULL;
	ret = (char *)ft_calloc(1, len + 1);
	if (ret == NULL)
		return (NULL);
	ret[len] = '\0';
	return (ret);
}

char	*ft_strcat_quote(char *s1, char *s2, int quote)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s1[i])
		i++;
	while (s2[j])
	{
		if (quote == 1 && s2[j] == SPACE)
			s1[i] = SPE_QUOTE;
		else
			s1[i] = s2[j];
		i++;
		j++;
	}
	s1[i] = '\0';
	return (s1);
}

char	**malloc_arg_and_return(int len)
{
	char	**ret;

	ret = NULL;
	ret = (char **)malloc(sizeof(char *) * (len + 1));
	if (ret == NULL)
		return (NULL);
	ret[len] = NULL;
	return (ret);
}
