/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tale-fau <tale-fau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 17:16:13 by mqueguin          #+#    #+#             */
/*   Updated: 2022/02/23 17:50:03 by tale-fau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_fill_sep(t_data *data, t_token *token,
		char *str, t_list_token *ls_token)
{
	if (data->sep_id == 1)
	{
		data->sep_id = 0;
		data->i++;
		return (SUCCESS);
	}
	else if (data->sep_id == 2)
	{
		data->i++;
		if (fill_content("|", token, &str[data->i], ls_token) == FAILURE)
			return (FAILURE);
	}
	else if (data->sep_id == 3)
	{
		data->i += 2;
		if (fill_content("<<", token, &str[data->i], ls_token) == FAILURE)
			return (FAILURE);
	}
	else if (data->sep_id > 3)
		if (ft_fill_sep_next_part(data, token, str, ls_token) == FAILURE)
			return (FAILURE);
	data->sep_id = 0;
	return (SUCCESS);
}

int	is_quote_inside(char *str)
{
	int	i;
	int	cnt;

	cnt = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == SINGLE_QUOTE || str[i] == DOUBLE_QUOTE)
			cnt++;
		i++;
	}
	if (cnt < 1)
		return (FAILURE);
	else
	{
		if (str[0] == SINGLE_QUOTE || str[i] == SINGLE_QUOTE)
			return (FAILURE);
		if (str[0] == DOUBLE_QUOTE || str[i] == DOUBLE_QUOTE)
			return (FAILURE);
	}
	return (SUCCESS);
}

void	connect_by_state(t_list_token *ls_token, t_token *new,
			t_token *token, int state)
{
	if (state == 1)
	{
		if (token->prev)
		{
			new->prev = token->prev;
			token->prev->next = new;
		}
		else
			ls_token->front = new;
	}
	else
	{
		new->prev = token;
		token->next = new;
	}
}

void	connect_last_token(t_list_token *ls_token, t_token *new, t_token *next)
{
	t_token	*tmp;

	if (next)
	{
		tmp = new;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = next;
		next->prev = tmp;
	}
	else
		ls_token->back = new;
}
