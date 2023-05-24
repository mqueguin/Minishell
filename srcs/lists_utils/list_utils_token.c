/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils_token.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqueguin <mqueguin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 15:57:08 by tale-fau          #+#    #+#             */
/*   Updated: 2022/02/27 19:08:29 by mqueguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_list_token	*init_list_token(t_token *node, t_list_token *ls_token)
{
	ls_token = (t_list_token *)malloc(sizeof(t_list_token));
	if (ls_token == NULL)
		return (NULL);
	else
	{
		ls_token->len2 = 0;
		ls_token->front = node;
		ls_token->back = node;
	}
	return (ls_token);
}

t_token	*init_node_token(t_token *node)
{
	node->id = 0;
	node->pipe_in_quote = 0;
	node->content = NULL;
	node->prev = NULL;
	node->next = NULL;
	node->space = 0;
	node->quote = 0;
	node->question_mark = 0;
	return (node);
}

int	is_empty_list_token(t_list_token *ls_token)
{
	if (ls_token == NULL)
		return (SUCCESS);
	else
		return (FAILURE);
}

int	list_length_token(t_list_token *ls_token)
{
	if (is_empty_list_token(ls_token) == SUCCESS)
		return (0);
	else
		return (ls_token->len2);
}

t_list_token	*add_back(t_list_token *ls_token)
{
	t_token	*new;

	new = (t_token *)malloc(sizeof(t_token));
	if (new == NULL)
		return (NULL);
	init_node_token(new);
	if (is_empty_list_token(ls_token) == SUCCESS)
		ls_token = init_list_token(new, ls_token);
	else
	{
		ls_token->back->next = new;
		new->prev = ls_token->back;
		ls_token->back = new;
	}
	ls_token->len2++;
	return (ls_token);
}
