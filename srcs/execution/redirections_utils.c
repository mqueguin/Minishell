/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tale-fau <tale-fau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 04:48:04 by tale-fau          #+#    #+#             */
/*   Updated: 2022/02/25 04:49:51 by tale-fau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	return_error_no_file(t_file *file)
{	
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(file->path, 2);
	ft_putstr_fd(": No such file or directory\n", 2);
	close(file->fd);
	change_status("1");
	return (FAILURE);
}

int	return_error_eacces(t_file *file)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(file->path, 2);
	ft_putstr_fd(": Permission denied\n", 2);
	change_status("1");
	return (FAILURE);
}

int	dup2_then_close(t_file *file)
{		
	file->fd = open(file->path, O_RDONLY);
	if (errno == EACCES)
		return (return_error_eacces(file));
	else if (file->fd < 0)
		return (return_error_no_file(file));
	if (dup2(file->fd, STDIN_FILENO) == -1)
		return (FAILURE);
	close(file->fd);
	return (SUCCESS);
}

int	dup2_then_close_the_sequel(t_file *file)
{
	int	fd;

	fd = open(file->heredoc_filename, O_RDONLY | O_CREAT, 0644);
	if (fd < 0)
		return (FAILURE);
	if (dup2(fd, STDIN_FILENO) < 0)
		return (FAILURE);
	close(fd);
	return (SUCCESS);
}
