/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqueguin <mqueguin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 11:13:28 by tale-fau          #+#    #+#             */
/*   Updated: 2022/02/06 23:37:15 by mqueguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	which_quote(char c, int state)
{
	if (c == SINGLE_QUOTE && state == 0)
		return (1);
	else if (state == 1 && c == SINGLE_QUOTE)
		return (0);
	if (c == DOUBLE_QUOTE && state == 0)
		return (2);
	else if (state == 2 && c == DOUBLE_QUOTE)
		return (0);
	return (0);
}

int	define_state(char c, int state)
{
	int	ret;

	ret = which_quote(c, state);
	return (ret);
}

char	*define_stop(int state)
{
	if (state == 1)
		return (ft_strdup("\'"));
	else if (state == 2)
		return (ft_strdup("\""));
	else
		return (ft_strdup("\'\""));
}

int	stop_writing(char c, char *stop)
{
	int	i;

	i = 0;
	while (stop[i])
	{
		if (stop[i] == c)
			return (SUCCESS);
		i++;
	}
	return (FAILURE);
}
