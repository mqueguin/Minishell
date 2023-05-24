/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils_token2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tale-fau <tale-fau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 16:02:16 by tale-fau          #+#    #+#             */
/*   Updated: 2022/02/28 14:59:01 by tale-fau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_list_token	*add_front(t_list_token *ls_token)
{
	t_token	*new;

	new = malloc(sizeof(*new));
	if (new == NULL)
		return (NULL);
	init_node_token(new);
	if (is_empty_list_token(ls_token) == SUCCESS)
	{
		ls_token = init_list_token(new, ls_token);
		if (ls_token == NULL)
		{
			free(new);
			return (NULL);
		}
	}
	else
	{
		ls_token->front->prev = new;
		new->next = ls_token->front;
		ls_token->front = new;
	}
	ls_token->len2++;
	return (ls_token);
}

void	free_token(t_token *to_free)
{
	free(to_free->content);
	free(to_free);
	to_free = NULL;
}

void	free_token_list(t_token *to_free)
{
	if (to_free->next)
		free_token_list(to_free->next);
	free(to_free->content);
	free(to_free);
	to_free = NULL;
}

t_list_token	*clear_list_token(t_list_token *ls_token)
{
	t_token	*token;

	if (is_empty_list_token(ls_token) == FAILURE)
	{
		token = ls_token->front;
		if (token)
			free_token_list(token);
		free(ls_token);
	}
	return (NULL);
}
