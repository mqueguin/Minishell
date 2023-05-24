/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqueguin <mqueguin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 17:44:49 by tale-fau          #+#    #+#             */
/*   Updated: 2022/02/28 00:12:58 by mqueguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	copy_to_node(char **dest, char *str, int type)
{
	char	*stop;
	int		i;

	i = 0;
	stop = define_stop(type);
	while (str[i] && stop_writing(str[i], stop) == FAILURE)
		i++;
	*dest = ft_calloc(1, i + 1);
	if (*dest == NULL)
		return (FAILURE);
	*dest = ft_strncpy(*dest, str, i);
	free(stop);
	return (i);
}

int	copy_to_node_quotes(char **dest, char *str, int type)
{
	char	*stop;
	int		i;

	i = 1;
	stop = define_stop(type);
	while (str[i] && stop_writing(str[i], stop) == FAILURE)
		i++;
	i++;
	*dest = ft_calloc(1, i + 1);
	if (*dest == NULL)
		return (FAILURE);
	*dest = ft_strncpy(*dest, str, i);
	free(stop);
	return (i);
}

t_quotes	*verif_quotes_in_token(t_quotes *node, char *str, int i, int j)
{
	int	state;
	int	len;

	state = 0;
	len = ft_strlen(str);
	while (i < len)
	{
		state = define_state(str[i], state);
		if (state == 0)
			j = copy_to_node(&node->str, &str[i], 0);
		else if (state == 1)
			j = copy_to_node_quotes(&node->str, &str[i], 1);
		else if (state == 2)
			j = copy_to_node_quotes(&node->str, &str[i], 2);
		i += j;
		if (i >= len)
			break ;
		node->next = create_node_quote();
		if (node->next == NULL)
			return (NULL);
		node = node->next;
	}
	return (node);
}

int	find_quotes(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == DOUBLE_QUOTE || str[i] == SINGLE_QUOTE)
			return (SUCCESS);
		i++;
	}
	return (FAILURE);
}

char	*manage_quotes(char *str)
{
	t_quotes	*tmp;
	t_quotes	*node;
	char		*ret;

	if (find_quotes(str) == FAILURE)
		return (str);
	node = create_node_quote();
	if (node == NULL)
		return (NULL);
	tmp = node;
	node = verif_quotes_in_token(node, str, 0, 0);
	if (node == NULL)
		return (NULL);
	node = tmp;
	ret = join_nodes_in_tab(node);
	node = tmp;
	free_quote(node);
	if (str)
		ft_strdel(&str);
	return (ret);
}
