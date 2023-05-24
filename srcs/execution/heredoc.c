/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqueguin <mqueguin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 21:49:31 by mqueguin          #+#    #+#             */
/*   Updated: 2022/02/28 17:03:50 by tale-fau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_expand_var_and_fill_file(char *line, t_env *env, int count)
{
	char	*ret;

	ret = NULL;
	ret = ft_loop_expand(line, count, ret, env);
	if (ret == NULL)
	{
		free(line);
		return (NULL);
	}
	free(line);
	return (ret);
}

void	heredoc_loop(t_file *file, t_env *env)
{
	char	*line;

	set_sig(&interrupt_heredoc, SIGINT);
	set_sig(&interrupt_heredoc, SIGQUIT);
	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (ft_strncmp_check_len(line, file->path,
				ft_strlen(file->path)) == SUCCESS)
		{
			free(line);
			break ;
		}
		if (file->quote == 0)
		{
			line = ft_expand_var_and_fill_file(line, env, 0);
			if (line == NULL)
				exit(FAILURE);
		}
		ft_putendl_fd(line, file->fd);
	}
	exit(SUCCESS);
}

int	ft_heredoc(t_file *file, t_env *env)
{
	pid_t	pid;

	file->fd = open(file->heredoc_filename, O_RDONLY | O_WRONLY | O_TRUNC
			| O_CREAT, 0644);
	pid = fork();
	if (pid == -1)
	{
		ft_putstr_fd("minishell: Failed to fork processus\n", 2);
		return (FAILURE);
	}
	else if (pid == 0)
		heredoc_loop(file, env);
	else
	{
		ignore_sig(SIGQUIT);
		ignore_sig(SIGINT);
		wait_function(pid);
		handle_signal();
	}
	close(file->fd);
	return (SUCCESS);
}

int	init_heredoc(t_file *file, t_env *env)
{
	int	ret;

	while (file)
	{
		if (file->type == 3)
		{
			ret = ft_heredoc(file, env);
			close(file->fd);
			if (ft_atoi(g_status) >= 128)
				return (FAILURE);
			if (ret > 0)
				return (ret);
		}
		file = file->next;
	}
	return (SUCCESS);
}

int	ft_check_if_heredoc(t_node *node, t_env *env, int ret)
{
	t_file	*file;

	while (node)
	{
		file = node->file;
		while (file)
		{
			if (file->type == 3)
			{
				file->heredoc_filename
					= create_file_name_heredoc("/tmp/.heredoc_file");
				if (file->heredoc_filename == NULL)
				{
					ft_putstr_fd("minishell: Memory allocation failed\n", 2);
					return (FAILURE);
				}
				ret = init_heredoc(file, env);
				if (ret > 0)
					return (ret);
			}
			file = file->next;
		}
		node = node->next;
	}
	return (SUCCESS);
}
