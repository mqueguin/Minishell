/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqueguin <mqueguin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 18:15:27 by tale-fau          #+#    #+#             */
/*   Updated: 2022/02/27 21:10:54 by mqueguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(char *cmd)
{
	if (ft_strncmp_check_len(cmd, "cd", 2) == SUCCESS)
		return (return_status_success());
	else if (ft_strncmp_check_len(cmd, "pwd", 3) == SUCCESS)
		return (return_status_success());
	else if (ft_strncmp_check_len(cmd, "echo", 4) == SUCCESS)
		return (return_status_success());
	else if (ft_strncmp_check_len(cmd, "env", 3) == SUCCESS)
		return (return_status_success());
	else if (ft_strncmp_check_len(cmd, "exit", 4) == SUCCESS)
		return (SUCCESS);
	else if (ft_strncmp_check_len(cmd, "unset", 5) == SUCCESS)
		return (return_status_success());
	else if (ft_strncmp_check_len(cmd, "export", 6) == SUCCESS)
		return (return_status_success());
	return (FAILURE);
}

t_env	*recover_index_path(t_env *env, int *j, char *str)
{
	int	len;

	len = 0;
	while (env)
	{
		len = 0;
		while (env->env[len] != '=' && env->env[len] != '\0')
			len++;
		if (ft_strncmp(env->env, str, len) == 0)
			break ;
		env = env->next;
	}
	if (env == NULL)
		return (env);
	while (env->env[*j] != '=')
		*j += 1;
	*j += 1;
	return (env);
}

char	*ft_strcat_exec(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*ret;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	i = ft_strlen(s1) + ft_strlen(s2);
	j = 0;
	ret = malloc(sizeof(char) + i);
	if (ret == NULL)
		return (NULL);
	while (s1[j])
	{
		ret[j] = s1[j];
		j++;
	}
	i = 0;
	while (s2[i])
		ret[j++] = s2[i++];
	ret[j] = '\0';
	if (s1)
		free(s1);
	return (ret);
}

char	*concat_cmd_opt_args(char *str, t_node *node)
{
	int	i;

	i = 0;
	if (node->option != NULL)
	{
		str = ft_strcat_exec(str, " ");
		str = ft_strcat_exec(str, node->option);
	}
	while (node->arg && node->arg[i] != NULL)
	{
		str = ft_strcat_exec(str, " ");
		str = ft_strcat_exec(str, node->arg[i++]);
	}
	return (str);
}

char	*concatenation_builtins_for_execve(char *str, char *path, t_node *node)
{
	str = ft_strdup(path);
	str = ft_strcat_exec(str, "/");
	str = ft_strcat_exec(str, node->cmd);
	str = concat_cmd_opt_args(str, node);
	return (str);
}
