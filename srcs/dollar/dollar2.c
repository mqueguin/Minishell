/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqueguin <mqueguin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 12:34:56 by tale-fau          #+#    #+#             */
/*   Updated: 2022/02/28 14:21:27 by mqueguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_dollar(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == DOLLAR && str[i + 1] && str[i + 1] != DOLLAR)
			return (SUCCESS);
		i++;
	}
	return (FAILURE);
}

int	is_separator(char c)
{
	if (c == SPACE || c == PIPE || c == DOLLAR
		|| c == SINGLE_QUOTE || c == DOUBLE_QUOTE || c == '\0')
		return (SUCCESS);
	else
		return (FAILURE);
}

char	*find_equivalent_with_name(t_env *env, char *str)
{
	int		i;
	char	*ret;

	i = 0;
	env = find_index_in_env(env, &i, str);
	if (env == NULL)
		ret = ft_strdup("\0");
	else
		ret = ft_strdup(env->env + i);
	return (ret);
}

int	fill_buffer_with_env_var(char *buf, char c, int *k, int *j)
{
	buf[*k] = c;
	*k += 1;
	*j += 1;
	if (*k > 999)
	{
		ft_putstr_fd("minishell: Invalid env variable.\n", 2);
		return (FAILURE);
	}
	return (SUCCESS);
}
