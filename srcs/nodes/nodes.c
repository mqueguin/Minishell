/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nodes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqueguin <mqueguin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 14:18:10 by tale-fau          #+#    #+#             */
/*   Updated: 2022/02/28 14:13:12 by mqueguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_token	*manage_redirections(t_token *token, t_node **node,
	t_list_token *ls_token, t_list *t_list_node)
{
	int	ret;

	ret = 0;
	token = ft_check_redirection(token, node, &ret, t_list_node);
	if (ret == 1)
		return (NULL);
	*node = t_list_node->head;
	while (token)
	{
		fill_id(token);
		if (!token->next)
			break ;
		token = token->next;
	}
	ls_token->back = token;
	while (token && token->prev)
		token = token->prev;
	ls_token->front = token;
	return (token);
}

static t_token	*ft_manage_node_init(t_list *t_list_node,
	t_node **node, t_list_token *ls_token)
{
	t_token	*token;

	*node = t_list_node->head;
	token = ls_token->front;
	token = manage_redirections(token, node, ls_token, t_list_node);
	if (token == NULL)
		return (NULL);
	token = ls_token->front;
	return (token);
}

t_token	*manage_assign_to_node(t_node **node, t_token *token,
	t_token *tmp, t_list **t_list_node)
{
	int	i;

	i = 0;
	*node = assign_token_to_node(*node, &token, &i);
	if (i == 2)
		token = token->next;
	if (token == tmp)
	{
		if (*node == NULL)
			return (NULL);
		if (!(*node)->cmd && (*node)->option)
			return (NULL);
		if (token->id == PIPE_ID)
		{
			(*node)->pipe = 1;
			if (!(*node)->next)
				add_tail(*t_list_node);
			(*node) = (*node)->next;
		}
		token = token->next;
	}
	return (token);
}

t_list	*manage_nodes(t_list_token *ls_token, t_list *t_list_node)
{
	t_token	*token;
	t_node	*node;
	t_token	*tmp;

	t_list_node = add_head(t_list_node);
	if (t_list_node == NULL)
		return (NULL);
	token = ft_manage_node_init(t_list_node, &node, ls_token);
	tmp = token;
	while (token)
	{
		tmp = token;
		if ((token->content[0] == '\0' && token->space == 0)
			|| (token->content[0] != '\0' && (token->space == 1
					|| token->space == 0)))
		{
			token = manage_assign_to_node(&node, token, tmp, &t_list_node);
		}
		else
			token = token->next;
	}
	clear_list_token(ls_token);
	return (t_list_node);
}
