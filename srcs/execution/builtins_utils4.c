/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils4.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqueguin <mqueguin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 03:54:31 by tale-fau          #+#    #+#             */
/*   Updated: 2022/02/25 20:35:15 by mqueguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*malloc_into_line(int size)
{
	char	*line;

	line = malloc(sizeof(char) * (size + 1));
	if (line == NULL)
		return (NULL);
	if (size == 0)
	{
		line[0] = '\0';
		return (line);
	}
	return (line);
}

char	*fill_cmd(char *node_str, char *str, int *size, int i)
{
	int		j;
	int		k;
	char	*line;

	j = -1;
	k = 0;
	line = malloc_into_line(size[1]);
	if (line == NULL)
		return (NULL);
	if (size[1] == 0)
	{
		line[0] = '\0';
		return (line);
	}
	while (node_str[i] && node_str[i] == ' ')
		line[k++] = node_str[i++];
	while (str[++j] && k < size[0])
		if (str[j] != ' ' && str[j] != '\0')
			line[k++] = str[j];
	while (node_str[i] && node_str[i] != ' ')
		i++;
	while (node_str[i] && node_str[i] == ' ')
		line[k++] = node_str[i++];
	line[k] = '\0';
	return (line);
}

int	*ft_get_size_cmd(char *str, char *node_str, int i, int j)
{
	int		*size;

	size = malloc(sizeof(int) * 2);
	if (size == NULL)
		return (NULL);
	size[0] = 0;
	size[1] = 0;
	while (str[++j])
	{
		if (str[j] != ' ')
		{
			size[0]++;
			if (str[j] != ' ' && str[j + 1] == ' ')
				break ;
		}
	}
	j = 0;
	while (node_str[++i])
	{
		if (node_str[i] == ' ')
			size[1]++;
		else if (node_str[i] != ' ' && j++ == 0)
			size[1] += size[0];
	}
	return (size);
}

char	*ft_fill_cmd_or_opt_or_args(char *node_str, char *str,
	int b_cmd_or_opt)
{
	char	*line;
	int		*size;

	if (b_cmd_or_opt == 1)
	{
		size = ft_get_size_cmd(str, node_str, -1, -1);
		if (size == NULL)
			return (NULL);
		line = fill_cmd(node_str, str, size, 0);
		if (line == NULL)
		{
			ft_putstr_fd("minishell: Memory allocation failed\n", 2);
			free(size);
			return (NULL);
		}
		free(size);
		return (line);
	}
	else
		line = ft_strdup(node_str);
	return (line);
}
