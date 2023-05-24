/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqueguin <mqueguin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 19:58:09 by mqueguin          #+#    #+#             */
/*   Updated: 2022/02/27 19:20:03 by mqueguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cmd_compare(t_env **env, t_node *node, int fork, int select)
{
	int		ret;

	ret = 0;
	if (ft_strncmp_check_len(node->cmd, "cd", 2) == SUCCESS)
		ret = cmd_cd(*env, fork, node);
	else if ((ft_strncmp_check_len(node->cmd, "pwd", 3) == SUCCESS)
		&& (select != 10))
		ret = cmd_pwd(*env);
	else if ((ft_strncmp_check_len(node->cmd, "echo", 4) == SUCCESS)
		&& (select != 10))
		ret = cmd_echo(node);
	else if ((ft_strncmp_check_len(node->cmd, "env", 3) == SUCCESS)
		&& (select != 10))
		ret = cmd_env(*env);
	else if (ft_strncmp_check_len(node->cmd, "exit", 4) == SUCCESS)
		ret = cmd_exit(*env, node, fork, 0);
	else if (ft_strncmp_check_len(node->cmd, "unset", 5) == SUCCESS)
		ret = cmd_unset(node, env, -1, fork);
	else if (ft_strncmp_check_len(node->cmd, "export", 6) == SUCCESS)
		ret = cmd_export(node, env, fork, -1);
	return (ret);
}

char	*loop_on_pathbin(char **pathbin, t_node *node, char **str, int i)
{
	int	fd;

	while (pathbin[i])
	{
		if (*str)
			free(*str);
		*str = concat_path_with_cmd(pathbin[i], node->cmd);
		if (*str == NULL)
			return (NULL);
		fd = open(*str, O_RDONLY);
		if (fd == -1)
		{
			if (pathbin[++i] == NULL)
			{
				free(*str);
				return (NULL);
			}
		}
		else
		{
			close(fd);
			break ;
		}
	}
	return (*str);
}

char	*recover_pathbin(t_node *node, t_env *env, int j, char *str)
{
	char	**pathbin;

	if (ft_check_if_cmd_content_slash(node->cmd) == SUCCESS)
	{
		str = ft_strdup_with_node(node);
		if (str == NULL)
			return (NULL);
		return (str);
	}
	env = recover_index_path(env, &j, "PATH");
	if (env == NULL)
	{
		if (str)
			free(str);
		str = ft_strdup(node->cmd);
		if (str == NULL)
			return (error_malloc_char());
		return (str);
	}
	pathbin = ft_split(env->env + j, ':');
	if (pathbin == NULL)
		return (NULL);
	str = loop_on_pathbin(pathbin, node, &str, 0);
	ft_free_tab(pathbin);
	return (str);
}

int	ft_error_execve(int err, char *msg)
{
	if (err == 0)
		ft_putstr_fd("minishell: Unable to execute\n", 2);
	else if (err == 1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(msg, 2);
		ft_putstr_fd(": is a directory\n", 2);
	}
	else if (err == 2)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(msg, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		return (127);
	}
	return (FAILURE);
}

int	ft_error_exec(int ret, char *cmd, int fork)
{
	if (ret == 127)
	{
		if (fork == 1)
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(cmd, 2);
			ft_putstr_fd(": command not found\n", 2);
		}
		return (127);
	}
	else if (ret == 2)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd("filename argument required\n", 2);
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": usage: . filename [arguments]\n", 2);
		return (2);
	}
	return (1);
}
