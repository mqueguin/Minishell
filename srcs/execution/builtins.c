/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqueguin <mqueguin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 10:58:01 by mqueguin          #+#    #+#             */
/*   Updated: 2022/02/28 15:58:34 by mqueguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*concat_path_with_cmd(char *pathbin, char *cmd)
{
	char	*str;

	str = ft_strdup(pathbin);
	if (str == NULL)
	{
		ft_putstr_fd("minishell: Memory allocation failed\n", 2);
		return (NULL);
	}
	str = ft_strcat_exec(str, "/");
	str = ft_strcat_exec(str, cmd);
	return (str);
}

int	is_not_builtin(t_node *node, int ret, char **path, t_env *env)
{
	*path = malloc(sizeof(char) * 5000);
	ft_bzero(*path, 5000);
	if (*path == NULL)
	{
		ft_putstr_fd("minishell: Memory allocation failed\n", 2);
		return (FAILURE);
	}
	if (node->cmd && ft_strcmp("..", node->cmd) == SUCCESS
		&& ft_strlen(node->cmd) == 2)
		ret = ft_error_exec(127, node->cmd, 0);
	else if (node->cmd && ft_strcmp(".", node->cmd) == SUCCESS
		&& ft_strlen(node->cmd) == 1)
		ret = ft_error_exec(2, node->cmd, 0);
	else if (node->cmd)
	{
		if (*path)
		{
			free(*path);
			*path = recover_pathbin(node, env, 0, NULL);
		}
		if (*path)
			*path = concat_cmd_opt_args(*path, node);
	}
	return (ret);
}

int	wait_exec(t_node *node, t_env **env)
{
	int	ret;
	int	status;

	while (node)
	{
		status = 0;
		waitpid(node->pid, &status, 0);
		if (WIFEXITED(status))
			ret = WEXITSTATUS(status);
		if (WIFSIGNALED(status))
		{
			ret = WTERMSIG(status);
			if (ret != 131)
				ret += 128;
		}
		if (node->cmd)
			cmd_compare(env, node, 0, 10);
		node = node->next;
	}
	handle_signal();
	return (ret);
}

int	loop_execution(t_node *node, t_env **env)
{
	char	*path;
	int		ret;

	ret = 0;
	path = NULL;
	if (node->cmd && node->cmd[0])
		if (is_builtin(node->cmd) == FAILURE)
			ret = is_not_builtin(node, ret, &path, *env);
	if (ret != 2)
	{
		if (start_fork_before_exec(node, path, env) == FAILURE)
		{
			if (path)
				free(path);
			return (FAILURE);
		}
	}
	free(path);
	return (SUCCESS);
}

int	ft_start_execution(t_env **env, t_list *t_list_node, int ret)
{
	t_node		*node;

	node = t_list_node->head;
	ret = ft_check_if_heredoc(node, *env, ret);
	if (ret > 0)
	{
		change_status("1");
		return (ret);
	}
	while (node != NULL)
	{
		ret = loop_execution(node, env);
		if (ret == FAILURE)
			return (FAILURE);
		node = node->next;
	}
	node = t_list_node->head;
	ret = wait_exec(node, env);
	if (g_status[0] == '0')
	{
		free(g_status);
		g_status = ft_itoa(ret);
	}
	return (SUCCESS);
}
