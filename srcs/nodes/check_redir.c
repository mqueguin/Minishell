/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tale-fau <tale-fau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 15:01:11 by tale-fau          #+#    #+#             */
/*   Updated: 2022/02/28 15:01:31 by tale-fau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*ft_check_redirection(t_token *token, t_node **node,
		int *ret, t_list *ls)
{
	t_file	*file;

	if (ft_check_token(token, node, ret, ls) == FAILURE)
		return (NULL);
	while ((*node)->prev)
		(*node) = (*node)->prev;
	while (!(*node)->file && (*node)->next)
		(*node) = (*node)->next;
	file = (*node)->file;
	while (file)
	{
		token = ft_erase_redirection_token(token, file);
		if (!file->next && (*node)->next)
		{
			(*node) = (*node)->next;
			while (!(*node)->file && (*node)->next)
				(*node) = (*node)->next;
			file = (*node)->file;
		}
		else if (file->next)
			file = file->next;
		else
			break ;
	}
	return (token);
}
