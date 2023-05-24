/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqueguin <mqueguin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 11:26:40 by mqueguin          #+#    #+#             */
/*   Updated: 2022/02/27 19:21:34 by mqueguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	ft_check_arg_zero(t_env *env, int fork)
{
	int	j;
	int	ret;

	j = 0;
	ret = 0;
	env = find_index_in_env(env, &j, "HOME");
	if (env == NULL)
	{
		if (fork)
			ft_putstr_fd("minishell: cd: HOME not set\n", 2);
		return (FAILURE);
	}
	ret = chdir(env->env + j);
	if (ret != 0 && fork == 1)
		return (ft_error_cd(env->env + j, errno));
	return (SUCCESS);
}

static char	*ft_recover_oldpath_or_new_path(t_env *env, char *str)
{
	char	*ret;
	int		j;
	t_env	*tmp;

	tmp = env;
	j = 0;
	env = find_index_in_env(env, &j, str);
	if (env == NULL)
		return (NULL);
	ret = ft_strdup(env->env + j);
	if (ret == NULL)
		return (NULL);
	env = tmp;
	return (ret);
}

int	ft_check_option_or_arg(char *dir, int fork)
{
	int	ret;

	ret = chdir(dir);
	if (ret != 0 && fork == 1)
		return (ft_error_cd(dir, errno));
	return (ret);
}

static int	ft_free_cd(char **s1, char **s2, int ret)
{
	if (*s1)
	{
		free(*s1);
		*s1 = NULL;
	}
	if (*s2)
	{
		free(*s2);
		*s2 = NULL;
	}
	return (ret);
}

int	cmd_cd(t_env *env, int fork, t_node *node)
{
	char	*new_path;
	char	*old_path;

	old_path = ft_recover_oldpath_or_new_path(env, "PWD");
	if (node->option)
	{
		if (ft_check_option_or_arg(node->option, fork) == FAILURE)
			return (FAILURE);
	}
	else if (node->arg[0] == NULL)
	{
		if (ft_check_arg_zero(env, fork) == FAILURE)
			return (FAILURE);
	}
	else if (node->arg[0][0] == '\0')
		return (SUCCESS);
	else
		if (ft_check_option_or_arg(node->arg[0], fork) == FAILURE)
			return (FAILURE);
	new_path = getcwd(NULL, 0);
	if (new_path == NULL)
		new_path = ft_recover_oldpath_or_new_path(env, "PWD");
	if (change_pwd_env(env, new_path, old_path) == FAILURE)
		return (ft_free_cd(&new_path, &old_path, FAILURE));
	return (ft_free_cd(&new_path, &old_path, SUCCESS));
}
