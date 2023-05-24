/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nodes_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqueguin <mqueguin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 14:21:42 by tale-fau          #+#    #+#             */
/*   Updated: 2022/02/27 21:07:18 by mqueguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_node	*assign_token_to_node(t_node *node, t_token **token, int *i)
{
	if ((*token)->id != PIPE_ID)
	{
		if ((*token)->id == ARG)
		{
			*token = arg_filler(*token, &node->arg);
			if (*token == NULL)
				return (NULL);
		}
		else if ((*token)->id == OPTION)
		{
			if (node->option == NULL)
			{
				*token = option_filler(*token, &node->option, &i);
				if (*token == NULL)
					return (NULL);
			}
		}
		else if ((*token)->id == CMD)
		{
			*token = cmd_filler(*token, &node->cmd, &i);
			if (*token == NULL)
				return (NULL);
		}
	}
	return (node);
}

int	count_quotes(char *str)
{
	int	ret;
	int	i;

	ret = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == SINGLE_QUOTE || str[i] == DOUBLE_QUOTE)
			ret++;
		i++;
	}
	return (ret);
}

int	ft_strlen_without_quotes(char *s)
{
	size_t	i;
	size_t	ret;

	i = 0;
	ret = 0;
	if (s == NULL)
		return (0);
	while (s[i])
	{
		if (s[i] == SINGLE_QUOTE || s[i] == DOUBLE_QUOTE)
			ret++;
		i++;
	}
	return (i - ret);
}

char	*ft_strdup_without_quotes(char *str)
{
	char	*ret;
	int		len;
	int		i;
	int		j;

	i = 0;
	j = 0;
	len = ft_strlen_without_quotes(str);
	ret = (char *)malloc(sizeof(char) * len + 1);
	if (ret == NULL)
		return (NULL);
	ret[len] = '\0';
	while (str[i])
	{
		if (str[i] == SINGLE_QUOTE || str[i] == DOUBLE_QUOTE)
			;
		else
		{
			ret[j] = str[i];
			j++;
		}
		i++;
	}
	return (ret);
}

t_node	*error_check(void)
{
	ft_putstr_fd("Error, parsing error.\n", 2);
	return (NULL);
}
