/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status_variable.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqueguin <mqueguin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 18:36:45 by mqueguin          #+#    #+#             */
/*   Updated: 2022/02/26 00:41:03 by mqueguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	change_status(char *status)
{
	if (g_status)
		free(g_status);
	g_status = ft_strdup(status);
}

int	new_size_of_dollar_interogation(char *cmd)
{
	int	i;
	int	size;

	i = 0;
	size = 0;
	while (cmd[i])
	{
		if (cmd[i] == '$' && cmd[i + 1] == '?')
		{
			i += 2;
			size += ft_strlen(g_status);
		}
		else
		{
			size++;
			i++;
		}
	}
	return (size);
}

static char	*ft_fill_variable(char *new_str, char *copy_str,
	int size)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	k = 0;
	while (i < size)
	{
		if (copy_str[k] == '$' && copy_str[k + 1] == '?')
		{
			j = 0;
			while (g_status[j])
				new_str[i++] = g_status[j++];
			k += 2;
		}
		else
		{
			new_str[i] = copy_str[k];
			i++;
			k++;
		}
	}
	new_str[i] = '\0';
	return (new_str);
}

char	*transform_question_mark(char *str)
{
	int		size;
	char	*new_str;
	char	*copy_str;

	copy_str = ft_strdup(str);
	if (copy_str == NULL)
	{
		ft_putstr_fd("minishell: Memory allocation failed\n", 2);
		return (NULL);
	}
	size = new_size_of_dollar_interogation(str);
	new_str = malloc(sizeof(char) * (size + 1));
	if (new_str == NULL)
	{
		ft_putstr_fd("minishell: Memory allocation failed\n", 2);
		return (NULL);
	}
	new_str = ft_fill_variable(new_str, copy_str, size);
	free(str);
	free(copy_str);
	return (new_str);
}
