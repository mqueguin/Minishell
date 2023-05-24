/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd2.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqueguin <mqueguin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 22:15:10 by mqueguin          #+#    #+#             */
/*   Updated: 2022/02/27 19:26:03 by mqueguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_error_cd(char *str, int b_err)
{
	if (b_err == 2)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
	}
	else if (b_err == 1)
		ft_putstr_fd("minishell: cd: environement variable PWD is empty\n", 2);
	else if (b_err == 13)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": Permission denied\n", 2);
	}
	else if (b_err == 20)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": Not a directory\n", 2);
	}
	return (FAILURE);
}

int	free_and_cat_exec(t_env *env, char *new_path)
{
	free(env->env);
	env->env = ft_strjoin("PWD=", new_path);
	if (env->env == NULL)
	{
		ft_error_cd(NULL, 2);
		return (FAILURE);
	}
	return (SUCCESS);
}

int	change_pwd_env(t_env *env, char *new_path, char *old_path)
{
	int		j;
	t_env	*tmp;

	j = 0;
	tmp = env;
	env = recover_index_path(env, &j, "PWD");
	if (env != NULL)
		if (free_and_cat_exec(env, new_path) == FAILURE)
			return (FAILURE);
	j = 0;
	env = recover_index_path(env, &j, "OLDPWD");
	if (env == NULL)
	{
		env = tmp;
		return (SUCCESS);
	}
	free(env->env);
	env->env = ft_strjoin("OLDPWD=", old_path);
	if (env->env == NULL)
		return (ft_error_cd(NULL, 2));
	env = tmp;
	return (SUCCESS);
}
