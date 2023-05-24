/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqueguin <mqueguin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 16:22:29 by tale-fau          #+#    #+#             */
/*   Updated: 2022/02/27 21:13:22 by mqueguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_list	*init_list(t_node *node, t_list *t_list_node)
{
	t_list_node = malloc(sizeof(t_list));
	if (t_list_node == NULL)
		return (NULL);
	else
	{
		t_list_node->len = 0;
		t_list_node->head = node;
		t_list_node->tail = node;
	}
	return (t_list_node);
}

t_node	*init_node(t_node *node)
{
	node->cmd = NULL;
	node->option = NULL;
	node->arg = (char **)malloc(sizeof(char *));
	if (node->arg == NULL)
		return (NULL);
	node->arg[0] = NULL;
	node->pipe = 0;
	node->fdhere = 0;
	node->question_mark = 0;
	node->file = NULL;
	node->nb_redirections = 0;
	node->prev = NULL;
	node->next = NULL;
	return (node);
}

int	is_empty_list(t_list *t_list_node)
{
	if (!t_list_node)
		return (SUCCESS);
	else
		return (FAILURE);
}

int	list_length(t_list *t_list_node)
{
	if (is_empty_list(t_list_node) == SUCCESS)
		return (0);
	else
		return (t_list_node->len);
}

t_list	*add_tail(t_list *t_list_node)
{
	t_node	*new;

	new = malloc(sizeof(*new));
	if (new == NULL)
		return (NULL);
	init_node(new);
	if (new == NULL)
		return (NULL);
	if (is_empty_list(t_list_node) == SUCCESS)
	{
		t_list_node = init_list(new, t_list_node);
		if (t_list_node == NULL)
			return (NULL);
	}
	else
	{
		t_list_node->tail->next = new;
		new->prev = t_list_node->tail;
		t_list_node->tail = new;
	}
	t_list_node->len++;
	return (t_list_node);
}
