/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tale-fau <tale-fau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 15:31:50 by tale-fau          #+#    #+#             */
/*   Updated: 2022/02/28 15:03:40 by tale-fau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*add_head(t_list *t_list_node)
{
	t_node	*new;

	new = malloc(sizeof(*new));
	if (new == NULL)
		return (NULL);
	init_node(new);
	if (is_empty_list(t_list_node) == SUCCESS)
	{
		t_list_node = init_list(new, t_list_node);
		if (t_list_node == NULL)
			return (NULL);
	}
	else
	{
		t_list_node->head->prev = new;
		new->next = t_list_node->head;
		t_list_node->head = new;
	}
	t_list_node->len++;
	return (t_list_node);
}

void	free_file_list(t_file *file)
{
	if (file->next != NULL)
		free_file_list(file->next);
	if (file->heredoc_filename)
	{
		unlink(file->heredoc_filename);
		free(file->heredoc_filename);
	}
	if (file->path)
		free(file->path);
	free(file);
}

void	free_node(t_node *to_free)
{
	if (to_free->arg)
		ft_free_tab(to_free->arg);
	if (to_free->cmd)
		free(to_free->cmd);
	if (to_free->option)
		free(to_free->option);
	if (to_free->file)
		free_file_list(to_free->file);
	free(to_free);
}

t_list	*list_del_tail(t_list *t_list_node)
{
	t_node	*tmp;

	if (is_empty_list(t_list_node) == SUCCESS)
	{
		ft_putstr("Nothing to delete, t_list_node is already empty.\n");
		return (NULL);
	}
	if (t_list_node->head == t_list_node->tail)
	{
		free_node(t_list_node->head);
		t_list_node->head = NULL;
		t_list_node->tail = NULL;
		return (NULL);
	}
	tmp = t_list_node->tail;
	t_list_node->tail = t_list_node->tail->prev;
	t_list_node->tail->next = NULL;
	tmp->next = NULL;
	tmp->prev = NULL;
	free_node(tmp);
	tmp = NULL;
	t_list_node->len--;
	return (t_list_node);
}

t_list	*list_del_head(t_list *t_list_node)
{
	t_node	*tmp;

	if (is_empty_list(t_list_node) == SUCCESS)
	{
		ft_putstr("Nothing to delete, t_list_node is already empty.\n");
		return (NULL);
	}
	if (t_list_node->head == t_list_node->tail)
	{
		free_node(t_list_node->head);
		t_list_node->head = NULL;
		t_list_node->tail = NULL;
		return (NULL);
	}
	tmp = t_list_node->head;
	t_list_node->head = t_list_node->head->next;
	t_list_node->head->prev = NULL;
	tmp->next = NULL;
	tmp->prev = NULL;
	free_node(tmp);
	tmp = NULL;
	t_list_node->len--;
	return (t_list_node);
}
