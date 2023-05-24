/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   post_tokenizer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqueguin <mqueguin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 11:24:43 by tale-fau          #+#    #+#             */
/*   Updated: 2022/02/28 00:55:01 by mqueguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	working_quote_number(char *str)
{
	int		i;
	int		quotes;
	char	quote_type;

	i = 0;
	quotes = 0;
	while (str[i])
	{
		if (str[i] == SINGLE_QUOTE || str[i] == DOUBLE_QUOTE)
		{
			quote_type = str[i++];
			quotes += 2;
			while (str[i] && str[i] != quote_type)
				i++;
		}
		if (!str[i])
			break ;
		i++;
	}
	if (quotes > 2)
		return (FAILURE);
	else
		return (SUCCESS);
}

int	quote_is_starting_or_ending(char *str)
{
	int	len;

	len = ft_strlen(str) - 1;
	if ((str[0] == SINGLE_QUOTE || str[0] == DOUBLE_QUOTE)
		&& (str[len] == SINGLE_QUOTE || str[len] == DOUBLE_QUOTE))
		return (FAILURE);
	if ((str[0] == SINGLE_QUOTE || str[0] == DOUBLE_QUOTE)
		&& (str[len] != SINGLE_QUOTE || str[len] != DOUBLE_QUOTE))
		return (SUCCESS);
	if ((str[0] != SINGLE_QUOTE || str[0] != DOUBLE_QUOTE)
		&& (str[len] == SINGLE_QUOTE || str[len] == DOUBLE_QUOTE))
		return (SUCCESS);
	return (FAILURE);
}

int	token_is_complex(t_token *token)
{
	if (!token->content)
		return (FAILURE);
	if (working_quote_number(token->content) == FAILURE)
		return (SUCCESS);
	if (quote_is_starting_or_ending(token->content) == SUCCESS)
		return (SUCCESS);
	if (is_quote_inside(token->content) == SUCCESS)
		return (SUCCESS);
	return (FAILURE);
}

t_token	*handle_complex_token(t_list_token *ls_token, t_token *token,
		char *new_token_address, int state)
{
	t_token	*new;

	new = NULL;
	if (good_arguments(new_token_address))
	{
		new = create_token_with_quote(&new_token_address, state);
		if (new == NULL)
			return (NULL);
		connect_by_state(ls_token, new, token, state);
		handle_complex_token(ls_token, new, new_token_address, 2);
	}
	else if (good_argums(new_token_address))
	{
		new = create_token_without_quote(&new_token_address, state);
		if (new == NULL)
			return (NULL);
		connect_by_state(ls_token, new, token, state);
		handle_complex_token(ls_token, new, new_token_address, 2);
	}
	return (new);
}

int	token_handler(t_list_token *ls_token)
{
	t_token	*token;
	t_token	*new;

	token = ls_token->front;
	while (token)
	{
		if (token_is_complex(token) == SUCCESS)
		{
			new = handle_complex_token(ls_token, token, token->content, 1);
			if (new == NULL)
				return (FAILURE);
			connect_last_token(ls_token, new, token->next);
			free_token(token);
			token = new;
		}
		token = token->next;
	}
	return (SUCCESS);
}
