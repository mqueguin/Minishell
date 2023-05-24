/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_node.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tale-fau <tale-fau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 02:44:31 by mqueguin          #+#    #+#             */
/*   Updated: 2022/02/27 17:10:35 by tale-fau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_quote(t_quotes *node)
{
	t_quotes	*tmp;

	while (node)
	{
		tmp = node;
		node = node->next;
		free(tmp->str);
		free(tmp);
	}
}
