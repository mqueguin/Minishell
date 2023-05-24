/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   post_tokenizer_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tale-fau <tale-fau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 21:31:51 by tale-fau          #+#    #+#             */
/*   Updated: 2022/02/24 21:58:32 by tale-fau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	content_null_or_not(t_token *token, t_data *data,
	t_list_token *ls_token, char *str)
{
	if (token->content != NULL)
	{
		if (ft_fill_sep(data, token->next, str, ls_token) == FAILURE)
			return (FAILURE);
	}
	else
	{
		if (ft_fill_sep(data, token, str, ls_token) == FAILURE)
			return (FAILURE);
	}
	return (SUCCESS);
}

int	good_arguments(char *new_token_address)
{
	return (new_token_address[0]
		&& (new_token_address[0] == SINGLE_QUOTE
			|| new_token_address[0] == DOUBLE_QUOTE));
}

int	good_argums(char *new_token_address)
{
	return (new_token_address[0]
		&& (new_token_address[0] != SINGLE_QUOTE
			&& new_token_address[0] != DOUBLE_QUOTE));
}
