/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipes_utils2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tale-fau <tale-fau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 12:57:04 by tale-fau          #+#    #+#             */
/*   Updated: 2022/02/14 13:56:12 by tale-fau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_and_return(int *index, int *i, char *str, int b_is_quote)
{
	if (str[*i] == '\0')
	{
		index[0] = -1;
		index[1] = -1;
		return (FAILURE);
	}
	if (str[*i] == SINGLE_QUOTE || str[*i] == DOUBLE_QUOTE)
	{
		if (b_is_quote == 1 && str[*i] == SINGLE_QUOTE)
			return (SUCCESS);
		else if (b_is_quote == 2 && str[*i] == DOUBLE_QUOTE)
			return (SUCCESS);
	}
	return (FAILURE);
}

void	ft_loop_for_search_quotes(char *str, int *copy_i, int b_is_quote)
{
	while (str[*copy_i])
	{
		if ((str[*copy_i] == '\'' && b_is_quote == 1)
			|| (str[*copy_i] == '\"' && b_is_quote == 2))
			break ;
		*copy_i += 1;
	}
}
