/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_or_transfer_fd.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqueguin <mqueguin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 20:57:22 by mqueguin          #+#    #+#             */
/*   Updated: 2022/02/25 20:57:52 by mqueguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_node	*ft_close_or_transfer_fd(t_node *node, int new_fd[2])
{
	if (node->prev != NULL)
	{
		close(node->prev->fd[0]);
		close(node->prev->fd[1]);
	}
	if (node->next != NULL)
	{
		node->fd[0] = new_fd[0];
		node->fd[1] = new_fd[1];
	}
	return (node);
}
