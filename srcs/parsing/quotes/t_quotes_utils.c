/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_quotes_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tale-fau <tale-fau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 18:50:15 by tale-fau          #+#    #+#             */
/*   Updated: 2022/02/23 17:54:44 by tale-fau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_quotes	*create_node_quote(void)
{
	t_quotes	*node;

	node = malloc(sizeof(t_quotes));
	if (node == NULL)
		return (NULL);
	node->str = NULL;
	node->next = NULL;
	return (node);
}
