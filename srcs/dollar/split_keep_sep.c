/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_keep_sep.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqueguin <mqueguin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 10:39:51 by tale-fau          #+#    #+#             */
/*   Updated: 2022/02/28 00:05:03 by mqueguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	specific_separtor(char *str, int i)
{
	if (str[i] == '\0')
		return (-1);
	if (str[i] && str[i] == '?' && i > 0 && str[i - 1] != '$')
		return (0);
	return (ft_isalnum(str[i]));
}

int	count_line(char *str, int i)
{
	int	size;

	size = 0;
	while (str[i])
	{
		while (specific_separtor(str, i) == 0)
		{
			size++;
			i++;
		}
		while (specific_separtor(str, i) == 1)
			i++;
		size++;
	}
	return (size);
}

char	*recover_line(char *str, int *start)
{
	char	*line;
	int		i;
	int		tmp;
	int		k;

	i = 0;
	tmp = *start;
	while (str[tmp])
	{
		if ((specific_separtor(str, tmp) == 0) && i > 0)
			break ;
		i++;
		tmp++;
	}
	line = malloc(sizeof(char) * (i + 1));
	if (line == NULL)
		return (NULL);
	k = 0;
	while (i > k)
	{
		line[k++] = str[*start];
		*start += 1;
	}
	line[k] = '\0';
	return (line);
}

char	**ft_split_not_erase_sep(char *str, int i, int j)
{
	char	**tab;

	tab = malloc(sizeof(char *) * (count_line(str, 0) + 1));
	if (tab == NULL)
		return (NULL);
	while (i < count_line(str, 0))
	{
		tab[i] = recover_line(str, &j);
		if (tab[i] == NULL)
		{
			ft_free_tab(tab);
			return (NULL);
		}
		i++;
	}
	tab[count_line(str, 0)] = 0;
	return (tab);
}
