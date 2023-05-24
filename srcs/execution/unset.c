/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqueguin <mqueguin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 22:57:58 by mqueguin          #+#    #+#             */
/*   Updated: 2022/02/28 01:57:21 by mqueguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	ft_delete_env(t_env **env, int delete_index)
{
	int		i;
	t_env	*to_free;
	t_env	*prev_to_free;

	to_free = *env;
	i = 0;
	if (delete_index == 0)
	{
		*env = (*env)->next;
		free(to_free->env);
		free(to_free);
		return ;
	}
	while (i < delete_index)
	{
		prev_to_free = to_free;
		to_free = to_free->next;
		i++;
	}
	if (to_free->next != NULL)
		prev_to_free->next = to_free->next;
	if (to_free->next == NULL)
		prev_to_free->next = NULL;
	free(to_free->env);
	free(to_free);
}

int	ft_check_args_is_valid(char *arg, int fork)
{
	int	i;

	i = 0;
	if (arg == NULL)
		return (FAILURE);
	while (arg[i])
	{
		while (arg[i] && arg[i] == '_')
			i++;
		if (arg[i] == '\0')
			break ;
		if (ft_check_is_alpha_or_num(arg[i], arg, 1, fork) == SUCCESS)
			if (ft_check_is_alpha_or_num(arg[i], arg, 2, fork) == FAILURE)
				return (FAILURE);
		i++;
	}
	return (SUCCESS);
}

void	find_index_unset(t_env **env, char *str)
{
	t_env	*tmp;
	int		len;
	int		delete_index;
	int		i;

	delete_index = 0;
	tmp = *env;
	i = 0;
	while (tmp)
	{
		len = ft_strlen(str);
		if (strncmp_for_dollar(tmp->env, str, len) == 0)
			return (ft_delete_env(env, delete_index));
		if (tmp->next)
			tmp = tmp->next;
		else
			break ;
		delete_index++;
	}
	return ;
}

int	cmd_unset(t_node *node, t_env **env, int i, int fork)
{
	int		ret;

	if (*env == NULL)
		return (FAILURE);
	ret = 0;
	while (node->arg[++i])
	{
		ret = ft_check_args_is_valid(node->arg[i], fork);
		if (ret == 0)
			find_index_unset(env, node->arg[i]);
	}
	return (ret);
}
