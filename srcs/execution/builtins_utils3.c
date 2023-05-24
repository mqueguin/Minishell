/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqueguin <mqueguin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 22:48:13 by mqueguin          #+#    #+#             */
/*   Updated: 2022/02/28 13:24:28 by mqueguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_count_words(t_node *node, char **option)
{
	int		i;
	int		count;

	i = -1;
	count = 0;
	if (node->cmd)
		count++;
	if (option)
		while (option[++i])
			count++;
	i = -1;
	while (node->arg[++i])
		count++;
	return (count);
}

char	**ft_split_with_error(t_node *node)
{
	char	**option;

	option = NULL;
	if (node->option)
	{
		option = ft_split(node->option, ' ');
		if (option == NULL)
		{
			ft_putstr_fd("minishell: Memory allocation failed\n", 2);
			return (NULL);
		}
		option = ft_search_and_replace(option);
	}
	return (option);
}

char	**fill_tab_with_option(char **option, char **tab, char *str, int *i)
{
	int	j;

	j = -1;
	while (option[++j])
	{
		*i += 1;
		tab[*i] = ft_fill_cmd_or_opt_or_args(option[j], str, 0);
		if (tab[*i] == NULL)
		{
			ft_free_tab(option);
			return ((char **)ft_free_tab(tab));
		}
	}
	return (tab);
}

char	*fill_tab_with_cmd(t_node *node, char *str)
{
	char	*ret;

	ret = NULL;
	if (node->cmd)
	{
		ret = ft_fill_cmd_or_opt_or_args(node->cmd, str, 1);
		if (ret == NULL)
			return (NULL);
	}
	return (ret);
}

char	**ft_translate_in_tab2d(t_node *node, char *str,
		char **tab, int i[2])
{
	char	**option;

	option = ft_split_with_error(node);
	if (node->option && option == NULL)
		return (NULL);
	tab = malloc(sizeof(char *) * (ft_count_words(node, option) + 1));
	if (tab == NULL)
		return (tab2d_return_null());
	tab[i[0]] = fill_tab_with_cmd(node, str);
	if (tab[i[0]] == NULL && node->cmd)
		return ((char **)ft_free_tab(tab));
	if (option)
	{
		tab = fill_tab_with_option(option, tab, str, &i[0]);
		if (tab == NULL)
			return (NULL);
	}
	while (node->arg[++i[1]])
	{
		tab[++i[0]] = ft_fill_cmd_or_opt_or_args(node->arg[i[1]], str, 0);
		if (tab[i[0]] == NULL)
			return ((char **)ft_free_tab(tab));
	}
	tab[ft_count_words(node, option)] = 0;
	return (tab);
}
