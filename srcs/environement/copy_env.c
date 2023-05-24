/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqueguin <mqueguin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 09:57:01 by mqueguin          #+#    #+#             */
/*   Updated: 2022/02/26 01:21:16 by mqueguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_free_env(t_env *env)
{
	t_env	*tmp;
	t_env	*next;

	tmp = env;
	while (tmp)
	{
		next = tmp->next;
		free(tmp->env);
		tmp->env = NULL;
		free(tmp);
		tmp = next;
	}
	free(tmp);
}

t_env	*create_node_env(char *str, int shlvl)
{
	t_env	*node;
	char	*itoa_ret;

	itoa_ret = NULL;
	node = malloc(sizeof(t_env));
	if (node == NULL)
		return (NULL);
	node->env = ft_strdup(str);
	if (node->env == NULL)
		return (NULL);
	if (ft_strncmp(node->env, "SHLVL", 5) == 0)
	{
		shlvl = ft_atoi(node->env + 6);
		shlvl++;
		free(node->env);
		itoa_ret = ft_itoa(shlvl);
		if (itoa_ret == NULL)
			return (NULL);
		node->env = ft_strjoin("SHLVL=", itoa_ret);
	}
	free(itoa_ret);
	node->next = NULL;
	return (node);
}

static void	check_if_shlvl_is_present(t_env **env, t_env *tmp)
{
	int	j;

	j = 0;
	*env = find_index_in_env(*env, &j, "SHLVL");
	if (*env == NULL)
	{
		*env = tmp;
		while ((*env)->next)
			*env = (*env)->next;
		(*env)->env = ft_strdup("SHLVL=1");
		if ((*env)->env == NULL)
		{
			*env = NULL;
			return ;
		}
		(*env)->next = NULL;
	}
	*env = tmp;
}

t_env	*copy_env(char **envp, int i)
{
	t_env	*tmp;
	t_env	*env;

	env = malloc(sizeof(t_env));
	if (env == NULL)
		return (error_malloc_t_env(env, 0));
	env->env = ft_strdup(envp[0]);
	if (env->env == NULL)
		return (error_malloc_t_env(env, 1));
	tmp = env;
	while (envp[++i])
	{
		env->next = create_node_env(envp[i], 0);
		if (env->next == NULL)
			return (NULL);
		env = env->next;
	}
	env = tmp;
	check_if_shlvl_is_present(&env, tmp);
	if (env == NULL)
		return (error_malloc_t_env(env, 1));
	return (env);
}
