/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipes_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tale-fau <tale-fau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 19:07:43 by mqueguin          #+#    #+#             */
/*   Updated: 2022/02/23 17:17:07 by tale-fau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_init_b_is_quote_and_copy_i(char c, int **i, int *copy_i)
{
	**i += 1;
	*copy_i = **i;
	if (c == '\'')
		return (1);
	else if (c == '\"')
		return (2);
	return (0);
}

static int	*ft_fill_len(int *len, int **number_pipes, int b_is_in_quote)
{
	if (b_is_in_quote == 0)
	{
		len[**number_pipes] = 0;
		**number_pipes += 1;
	}
	else if (b_is_in_quote == 1)
	{
		len[**number_pipes] = 1;
		**number_pipes += 1;
	}
	return (len);
}

static int	*ft_check_if_pipes_in_quotes(char *str, int *number_pipes,
				int *i, int *len)
{
	int	copy_i;
	int	b_is_quote;

	b_is_quote = ft_init_b_is_quote_and_copy_i(str[*i], &i, &copy_i);
	ft_loop_for_search_quotes(str, &copy_i, b_is_quote);
	if (str[copy_i] == '\0')
	{
		while (*i < copy_i)
		{
			if (str[*i] == '|')
				len = ft_fill_len(len, &number_pipes, 0);
			*i += 1;
		}
	}
	else
	{
		while (*i < copy_i)
		{
			if (str[*i] == '|')
				len = ft_fill_len(len, &number_pipes, 1);
			*i += 1;
		}
	}
	return (len);
}

static int	*ft_malloc_and_init_tab(char *str, int number_pipes)
{
	int	i;
	int	*len;

	i = -1;
	while (str[++i])
		if (str[i] == '|')
			number_pipes++;
	len = (int *)malloc(sizeof(int) * (number_pipes + 1));
	if (len == NULL)
		return (NULL);
	i = 0;
	while (i < number_pipes)
		len[i++] = 0;
	len[i] = -1;
	return (len);
}

int	*check_number_of_pipe_into_quotes(char *str, int number_pipes, int i)
{
	int	*len;
	int	j;

	len = ft_malloc_and_init_tab(str, number_pipes);
	if (len == NULL)
		return (NULL);
	j = 0;
	while (str[i])
	{
		if ((str[i] == '\'' || str[i] == '\"') && str[i + 1])
		{
			len = ft_check_if_pipes_in_quotes(str, &j, &i, len);
			if (str[i] && str[i + 1] && (str[i] == '\'' || str[i] == '\"'))
				i++;
		}
		else if (str[i] == '|')
		{
			len[j++] = 0;
			i++;
		}
		else
			i++;
	}
	return (len);
}
