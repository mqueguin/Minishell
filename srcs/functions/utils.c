/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqueguin <mqueguin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 14:50:42 by tale-fau          #+#    #+#             */
/*   Updated: 2022/02/28 16:12:19 by mqueguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_and_change_option(t_node **node)
{
	int	i;

	i = 0;
	if (!(*node)->option)
		return ;
	while ((*node)->option[i])
	{
		if ((*node)->option[i] == SPE_QUOTE)
			(*node)->option[i] = SPACE;
		i++;
	}
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0')
		i++;
	return (s1[i] - s2[i]);
}

char	*cut_line(char *str)
{
	int	i;

	i = skip_spaces(str);
	str += i;
	return (str);
}

int	skip_spaces(char *str)
{
	int	i;

	i = 0;
	while (str[i] == SPACE)
		i++;
	return (i);
}
