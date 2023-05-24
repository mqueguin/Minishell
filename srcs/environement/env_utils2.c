/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tale-fau <tale-fau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 19:14:17 by tale-fau          #+#    #+#             */
/*   Updated: 2022/02/27 15:40:56 by tale-fau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**create_envp(t_env *env, int i, int size_env)
{
	char	**my_envp;
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		size_env++;
		tmp = tmp->next;
	}
	my_envp = malloc(sizeof(char *) * (size_env + 1));
	if (my_envp == NULL)
		return (NULL);
	my_envp[size_env] = 0;
	tmp = env;
	while (tmp)
	{
		my_envp[i] = ft_strdup(tmp->env);
		if (my_envp[i++] == NULL)
		{
			ft_free_tab(my_envp);
			return ((char **)error_malloc_char());
		}
		tmp = tmp->next;
	}
	return (my_envp);
}

char	*loop_and_join(int i, char **tab, char *str)
{
	while (tab[i])
	{
		str = ft_strjoin_free_str(str, tab[i++], 1, 0);
		if (str == NULL)
			return (NULL);
	}
	return (str);
}

t_env	*add_new_var_to_copy_env(t_env *env, t_env *copy_env,
		t_env *tmp, char **tab)
{
	char	*str;

	str = ft_strjoin(tab[0], tab[1]);
	if (str == NULL)
		return (NULL);
	str = loop_and_join(2, tab, str);
	if (env == NULL)
	{
		while (copy_env->next != NULL)
			copy_env = copy_env->next;
		copy_env->next = create_node_env(str, 0);
		env = tmp;
	}
	else
	{
		while (copy_env != env)
			copy_env = copy_env->next;
		free(copy_env->env);
		copy_env->env = ft_strdup(str);
		env = tmp;
	}
	free(str);
	return (copy_env);
}

void	ft_display_env(t_env *env)
{
	while (env)
	{
		write(1, env->env, ft_strlen(env->env));
		write(1, "\n", 1);
		env = env->next;
	}
}

t_env	*body_env_function(char *arg, t_env *env,
	t_env *copy_env, t_env *tmp)
{
	int		j;
	char	**tab;

	j = 0;
	tab = ft_mini_split(arg, '=');
	if (tab == NULL)
	{
		ft_putstr_fd("minishell: env: memory allocation failed\n", 2);
		return (NULL);
	}
	env = find_index_in_env(env, &j, tab[0]);
	copy_env = tmp;
	copy_env = add_new_var_to_copy_env(env, copy_env, tmp, tab);
	if (copy_env == NULL)
	{
		ft_free_tab(tab);
		return (NULL);
	}
	ft_free_tab(tab);
	return (copy_env);
}
