/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqueguin <mqueguin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 19:01:11 by tale-fau          #+#    #+#             */
/*   Updated: 2022/02/27 22:21:57 by mqueguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	contains_bad_char(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == DASH && str[i + 1] == DASH)
			return (SUCCESS);
		if (str[i] == DASH || str[i] == 'n')
			;
		else
			return (SUCCESS);
		i++;
	}
	return (FAILURE);
}

char	*malloc_and_bzero(size_t len)
{
	char	*ret;

	ret = (char *)malloc(sizeof(*ret) * len);
	if (ret == NULL)
		return (NULL);
	ft_bzero(ret, ft_strlen(ret));
	return (ret);
}

char	*malloc_bzero_and_fill(size_t len, char *s1, char *s2, int space)
{
	char	*ret;
	int		i;
	int		j;

	ret = malloc_and_bzero(len);
	j = 0;
	i = 0;
	if (s1)
		while (s1[i])
			ret[j++] = s1[i++];
	i = 0;
	while (s2[i])
	{
		ret[j] = s2[i++];
		j++;
	}
	if (space == 1)
	{
		ret[j] = SPACE;
		ret[++j] = '\0';
	}
	else if (space == 2)
		ret[j] = '\0';
	return (ret);
}

char	*joinfree_with_space(char *s1, char *s2, int space)
{
	char	*ret;
	size_t	len;

	len = 0;
	if (!s2)
		return (NULL);
	if (space == 1)
		len = (ft_strlen(s1) + ft_strlen(s2)) + 2;
	else if (space == 2)
		len = (ft_strlen(s1) + ft_strlen(s2)) + 1;
	ret = malloc_bzero_and_fill(len, s1, s2, space);
	if (ret == NULL)
		return (NULL);
	if (s1)
		free(s1);
	return (ret);
}

char	*find_wrong_option(t_node *node, int *count)
{
	char	*ret;
	char	**tab;
	int		i;
	int		check;

	check = 0;
	i = 0;
	ret = NULL;
	tab = ft_split(node->option, SPACE);
	while (tab[i])
	{
		if (check != 1 && contains_bad_char(tab[i]) == SUCCESS)
			check = 1;
		if (check == 1 && (tab[i + 1]))
			ret = joinfree_with_space(ret, tab[i], 1);
		else if (check == 1 && !(tab[i + 1]))
			ret = joinfree_with_space(ret, tab[i], 2);
		i++;
	}
	if (check == 1)
		*count += 1;
	ft_free_tab(tab);
	return (ret);
}
