/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   joins.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqueguin <mqueguin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 11:23:06 by tale-fau          #+#    #+#             */
/*   Updated: 2022/02/27 23:16:49 by mqueguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	get_total_len(t_quotes *node)
{
	size_t	ret;
	int		i;

	i = 0;
	ret = 0;
	while (node->next)
	{
		i = 0;
		while (node->str[i])
		{
			i++;
			ret++;
		}
		node = node->next;
	}
	return (ret);
}

char	**dup_quotes_nodes_into_tab(t_quotes *node, int len)
{
	char		**ret;
	int			i;

	i = 0;
	ret = (char **)malloc(sizeof(char *) * (len + 1));
	if (ret == NULL)
		return (NULL);
	ret[len] = NULL;
	while (node)
	{
		ret[i] = ft_strdup(node->str);
		if (ret[i] == NULL)
			return ((char **)ft_free_tab(ret));
		node = node->next;
		i++;
	}
	return (ret);
}

char	*join_tab_in_ret(char **tab)
{
	int		i;
	char	*ret;

	i = 0;
	ret = NULL;
	while (tab[i])
	{
		if (!ret)
		{
			ret = ft_strdup(tab[i]);
			if (ret == NULL)
				return (ft_free_tab(tab));
		}
		else
		{
			ret = ft_strjoin_free_str(ret, tab[i], 1, 0);
			if (ret == NULL)
				return (ft_free_tab(tab));
		}
		i++;
	}
	ft_free_tab(tab);
	return (ret);
}

char	*join_nodes_in_tab(t_quotes *node)
{
	char		**tab;
	char		*ret;
	t_quotes	*tmp;
	int			i;

	i = 0;
	tmp = node;
	while (tmp)
	{
		i++;
		if (!tmp->next)
			break ;
		tmp = tmp->next;
	}
	tab = dup_quotes_nodes_into_tab(node, i);
	if (tab == NULL)
		return (NULL);
	ret = join_tab_in_ret(tab);
	return (ret);
}

int	get_len(t_quotes *node)
{
	t_quotes	*tmp;
	int			i;

	i = 0;
	tmp = node;
	while (tmp)
	{
		i++;
		if (!tmp->next)
			break ;
		tmp = tmp->next;
	}
	return (i);
}
