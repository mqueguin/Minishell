/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tale-fau <tale-fau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 17:16:27 by mqueguin          #+#    #+#             */
/*   Updated: 2022/02/28 16:39:34 by tale-fau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_check_if_option(t_node *node)
{
	char	**tab;

	if (!node->option)
		return (0);
	tab = ft_split(node->option, SPACE);
	if (contains_bad_char(tab[0]) == FAILURE)
		return (1);
	return (0);
}

int	cmd_echo(t_node *node)
{
	int		b_flag;
	int		count;
	int		i;

	count = 0;
	b_flag = ft_check_if_option(node);
	if (node->option)
		ft_putstr_fd(find_wrong_option(node, &count), 1);
	i = -1;
	while (node->arg[++i])
	{
		if (count == 1)
			write(1, " ", 1);
		ft_putstr_fd(node->arg[i], 1);
		if (node->arg[i + 1])
			write(1, " ", 1);
		if (count >= 1)
			count++;
	}
	if (b_flag == 0)
		write(1, "\n", 1);
	return (SUCCESS);
}
