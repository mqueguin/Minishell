/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils5.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqueguin <mqueguin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 17:49:49 by mqueguin          #+#    #+#             */
/*   Updated: 2022/02/25 20:35:21 by mqueguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**tab2d_return_null(void)
{
	ft_putstr_fd("minishell: Memory allocation failed\n", 2);
	return (NULL);
}

char	**ft_search_and_replace(char **option)
{
	int	i;
	int	j;

	i = 0;
	j = -1;
	while (option[i])
	{
		j = -1;
		while (option[i][++j])
		{
			if (option[i][j] == SPE_QUOTE)
				option[i][j] = SPACE;
		}
		i++;
	}
	return (option);
}

int	ft_check_if_cmd_content_slash(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '/')
			return (SUCCESS);
		i++;
	}
	return (FAILURE);
}

char	*ft_strdup_with_node(t_node *node)
{
	char	*str;

	str = ft_strdup(node->cmd);
	if (str == NULL)
		return (error_malloc_char());
	return (str);
}
