/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tale-fau <tale-fau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 15:26:31 by tale-fau          #+#    #+#             */
/*   Updated: 2022/02/27 14:59:23 by tale-fau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	are_there_multiple_dollar_sign(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == DOLLAR)
			count++;
		i++;
	}
	if (count > 1)
		return (SUCCESS);
	else
		return (FAILURE);
}

int	len_until_equal_sign(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	return (i);
}

int	strncmp_for_dollar(char *s1, char *s2, int len1)
{
	int	i;

	i = 0;
	if (len_until_equal_sign(s1) != len1)
		return (-1);
	while (s1[i] && s1[i] != '=')
	{
		if (s1[i] != s2[i])
			return (-1);
		i++;
	}
	return (0);
}

t_env	*find_index_in_env(t_env *env, int *j, char *str)
{
	int	len;
	int	check;

	check = 0;
	while (env)
	{
		len = ft_strlen(str);
		if (strncmp_for_dollar(env->env, str, len) == 0)
		{
			check = 1;
			break ;
		}
		env = env->next;
	}
	if (check == 0)
		return (NULL);
	while (env->env[*j] != '=')
		*j += 1;
	*j += 1;
	return (env);
}
