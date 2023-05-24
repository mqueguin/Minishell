/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tale-fau <tale-fau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 15:03:52 by tale-fau          #+#    #+#             */
/*   Updated: 2022/02/28 15:04:37 by tale-fau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_node_list(t_node *node)
{
	if (node && node->next)
		ft_free_node_list(node->next);
	if (node)
		free_node(node);
}

t_list	*clear_list(t_list *t_list_node)
{
	t_node	*node;

	if (t_list_node)
	{
		node = t_list_node->head;
		ft_free_node_list(node);
		if (t_list_node)
			free(t_list_node);
	}
	return (NULL);
}

void	create_redirection_node(t_node *node, char *file_name,
			int type, int is_quote)
{
	t_file	*new;
	t_file	*tmp;

	new = malloc(sizeof(t_file));
	if (new == NULL)
		return ;
	new->path = ft_strdup(file_name);
	new->type = type;
	new->quote = is_quote;
	new->fd = 0;
	new->pipes[0] = 0;
	new->pipes[1] = 0;
	new->heredoc_filename = NULL;
	new->next = NULL;
	if (!node->file)
		node->file = new;
	else
	{
		tmp = node->file;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}
