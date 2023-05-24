/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tale-fau <tale-fau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 14:24:57 by tale-fau          #+#    #+#             */
/*   Updated: 2022/02/14 14:02:33 by tale-fau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_if_multi_pipe(char *str, int i)
{
	if (str[i] == PIPE)
	{
		i++;
		while (str[i] && str[i] == SPACE)
			i++;
		if (str[i] == PIPE)
		{
			error(5);
			return (FAILURE);
		}
	}
	return (SUCCESS);
}

int	check_if_there_are_any_quotes(char *str, int i, int b_is_quote)
{
	int			j;
	static int	index_prev_quote_and_pipe[2] = {-1, -1};

	j = i;
	while (--j > 0)
		if (str[j] && (str[j] == SINGLE_QUOTE || str[j] == DOUBLE_QUOTE))
			break ;
	if (j < 0)
		return (FAILURE);
	if (str[j] == SINGLE_QUOTE || str[j] == DOUBLE_QUOTE)
	{
		if (str[j] == SINGLE_QUOTE)
			b_is_quote = 1;
		else if (str[j] == DOUBLE_QUOTE)
			b_is_quote = 2;
		index_prev_quote_and_pipe[0] = j;
		index_prev_quote_and_pipe[1] = i;
	}
	while (str[++i])
		if ((str[i] == SINGLE_QUOTE && b_is_quote == 1)
			|| (str[i] == DOUBLE_QUOTE && b_is_quote == 2))
			break ;
	return (check_and_return(index_prev_quote_and_pipe, &i, str, b_is_quote));
}

static int	add_space_before_an_after_pipe(char *str, int i)
{
	int	count;

	count = 0;
	if (str[i - 1] != SPACE)
		count++;
	if (str[i + 1] != SPACE)
		count++;
	return (count);
}

int	check_pipe_is_first_word(char *str, int i)
{
	int	j;

	j = i;
	while (--j >= 0)
		if (str[j] != SPACE)
			break ;
	if (j < 0)
		return (SUCCESS);
	i++;
	while (str[i] && str[i] == SPACE)
		i++;
	if (str[i] == '\0')
		return (SUCCESS);
	return (FAILURE);
}

int	parse_pipes(char *str, int i, int len, int *len_pipes)
{
	int			number_pipes;

	number_pipes = 0;
	while (str[++i])
	{
		if (str[i] == PIPE && len_pipes[number_pipes++] == 0)
		{
			if (check_pipe_is_first_word(str, i) == SUCCESS)
			{
				error(5);
				return (-42);
			}
			else if (str[i] == PIPE && !str[i + 1])
			{
				error(5);
				return (-42);
			}
			else if (str[i] == PIPE)
				len += add_space_before_an_after_pipe(str, i);
			if (check_if_multi_pipe(str, i) == FAILURE)
				return (-42);
		}
		len++;
	}
	return (len);
}
