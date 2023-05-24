/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tale-fau <tale-fau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 17:06:15 by tale-fau          #+#    #+#             */
/*   Updated: 2022/02/27 16:43:56 by tale-fau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_check_args(char *str, int fork, int i, int j)
{
	if (str[0] == '=')
		return (suite(fork, str));
	if (ft_is_digit(str[0]))
		return (suite(fork, str));
	if (str[0] == '\0')
		if (ft_check_is_alpha_or_num(str[++i], str, 3, fork) == FAILURE)
			return (FAILURE);
	while (str[++i])
		if (str[i] == '=')
			break ;
	while (++j < i)
	{
		if (str[j] == '_')
			j++;
		if (!str[j] || str[j] == '=')
			break ;
		if (!ft_check_is_alpha_or_num(str[j], str, 1, fork))
		{
			if (ft_check_is_alpha_or_num(str[i], str, 3, fork) == FAILURE)
				return (FAILURE);
		}
	}
	return (SUCCESS);
}

char	*cut_str(char *str)
{
	int		i;
	char	*ret;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	ret = (char *)malloc(sizeof(char) * i + 1);
	if (!ret)
		return (NULL);
	ret[i] = '\0';
	ret = ft_strncpy(ret, str, i);
	return (ret);
}

t_env	*index_in_env(t_env *env, char *str)
{
	int		len;
	int		check;
	char	*to_find;

	check = 0;
	to_find = cut_str(str);
	if (to_find == NULL)
		return (NULL);
	while (env)
	{
		len = ft_strlen(to_find);
		if (strncmp_for_dollar(env->env, to_find, len) == 0)
		{
			check = 1;
			break ;
		}
		env = env->next;
	}
	free(to_find);
	if (check == 0)
		return (NULL);
	return (env);
}

void	with_good_args(char *str, t_env **env)
{
	t_env	*tmp;

	tmp = NULL;
	if (ft_search_equal_char(str) == SUCCESS)
	{
		if ((*env)->env == NULL)
		{
			*env = create_node_env(str, 0);
			return ;
		}
		tmp = index_in_env(*env, str);
		if (tmp == NULL)
		{
			tmp = *env;
			while (tmp->next != NULL)
				tmp = tmp->next;
			tmp->next = create_node_env(str, 0);
		}
		else
		{
			free(tmp->env);
			tmp->env = ft_strdup(str);
		}
	}
}
