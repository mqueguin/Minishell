/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tale-fau <tale-fau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 14:21:23 by mqueguin          #+#    #+#             */
/*   Updated: 2022/02/25 04:49:52 by tale-fau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_check_is_output(t_file *file, t_node *node)
{
	if (file->type == 0)
	{
		file->fd = open(file->path, O_RDWR | O_CREAT | O_TRUNC, 0666);
		if (errno == EACCES)
			return (return_error_eacces(file));
		if (node->cmd)
			if (dup2(file->fd, STDOUT_FILENO) < 0)
				return (FAILURE);
		close(file->fd);
	}
	else if (file->type == 2)
	{
		file->fd = open(file->path, O_CREAT | O_RDWR | O_APPEND, 0644);
		if (errno == EACCES)
			return (return_error_eacces(file));
		if (dup2(file->fd, STDOUT_FILENO) < 0)
			return (FAILURE);
		close(file->fd);
	}
	change_status("0");
	return (SUCCESS);
}

static int	ft_check_is_input(t_node *node)
{
	t_file	*file;

	file = node->file;
	while (file)
	{
		if (file->type == 1)
		{
			if (dup2_then_close(file) == FAILURE)
				return (FAILURE);
		}
		else if (file->type == 3)
		{
			if (dup2_then_close_the_sequel(file) == FAILURE)
				return (FAILURE);
		}
		else
			if (ft_check_is_output(file, node) == FAILURE)
				return (FAILURE);
		file = file->next;
	}
	change_status("0");
	return (SUCCESS);
}

int	ft_redirection(t_node *node)
{
	if (ft_check_is_input(node) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}
