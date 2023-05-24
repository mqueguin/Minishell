/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqueguin <mqueguin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 13:19:51 by mqueguin          #+#    #+#             */
/*   Updated: 2022/02/27 19:03:13 by mqueguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	execution(t_node *node, char *str, t_env *env)
{
	char	**path;
	char	**tab;
	int		index[2];

	path = NULL;
	index[0] = 0;
	index[1] = -1;
	path = ft_translate_in_tab2d(node, str, path, index);
	if (path == NULL)
		exit(FAILURE);
	tab = create_envp(env, 0, 0);
	if (tab == NULL)
		return (FAILURE);
	if (execve(path[0], path, tab) == -1)
	{
		if (errno == 7)
			exit(ft_error_execve(0, path[0]));
		else if (errno == 13)
			exit(ft_error_execve(1, path[0]));
		else if (errno == 2)
			exit(ft_error_execve(2, path[0]));
	}
	ft_free_tab(tab);
	exit(FAILURE);
}

void	ft_dup_file_descriptor(t_node *node)
{
	t_file	*file;

	file = node->file;
	while (file)
	{
		if (file->type == 0 || file->type == 2)
			dup2(file->fd, 1);
		else if (file->type == 1)
			dup2(file->fd, 0);
		file = file->next;
	}
}

int	ft_dup_pipes(t_node *node, int new_fd[2])
{
	if (node->prev != NULL)
	{
		if (dup2(node->prev->fd[0], STDIN_FILENO) < 0)
			return (FAILURE);
		close(node->prev->fd[0]);
		close(node->prev->fd[1]);
	}
	if (node->next != NULL)
	{
		if (dup2(new_fd[1], STDOUT_FILENO) < 0)
			return (FAILURE);
		close(new_fd[0]);
		close(new_fd[1]);
	}
	return (SUCCESS);
}

int	process_child_execution(char *path, t_env **env,
		t_node *node, int new_fd[2])
{
	if (ft_dup_pipes(node, new_fd) == FAILURE)
		exit(FAILURE);
	if (ft_redirection(node) == FAILURE)
		exit(FAILURE);
	if (node->cmd == NULL)
		exit(ft_atoi(g_status));
	if (is_builtin(node->cmd) == SUCCESS)
	{
		check_and_change_option(&node);
		exit(cmd_compare(env, node, 1, 0));
	}
	if (path == NULL)
		exit(ft_error_exec(127, node->cmd, 1));
	if (execution(node, path, *env) == FAILURE)
		return (FAILURE);
	exit(FAILURE);
}

int	start_fork_before_exec(t_node *node, char *path, t_env **env)
{
	int	new_fd[2];

	if (node->next != NULL)
	{
		if (pipe(new_fd) == -1)
		{
			ft_putstr_fd("minishell: Failed to create pipe file descriptor\n",
				2);
			return (FAILURE);
		}
	}
	node->pid = fork();
	disable_signal(node->pid);
	if (node->pid == -1)
	{
		ft_putstr_fd("minishell: Failed to fork processus\n", 2);
		return (FAILURE);
	}
	else if (node->pid == 0)
		process_child_execution(path, env, node, new_fd);
	else
		node = ft_close_or_transfer_fd(node, new_fd);
	return (SUCCESS);
}
