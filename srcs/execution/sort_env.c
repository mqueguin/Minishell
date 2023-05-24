/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tale-fau <tale-fau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 17:07:31 by tale-fau          #+#    #+#             */
/*   Updated: 2022/02/25 02:14:23 by tale-fau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**malloc_the_tab(t_env *tmp_env)
{
	int		i;
	char	**tab;

	i = 0;
	while (tmp_env)
	{
		i++;
		tmp_env = tmp_env->next;
	}
	tab = malloc(sizeof(char *) * (i + 1));
	if (tab == NULL)
		return (NULL);
	tab[i] = NULL;
	return (tab);
}

char	*malloc_the_str(t_env *copy)
{
	char	*ret;

	ret = malloc(sizeof(char) * 5000);
	ft_bzero(ret, 5000);
	ret = ft_strcpy2(ret, copy->env);
	return (ret);
}

char	**sort_tab(char **tab, char *tmp)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		if (tab[i + 1] && ft_strcmp(tab[i], tab[i + 1]) > 0)
		{
			tmp = ft_strcpy2(tmp, tab[i]);
			tab[i] = ft_strcpy2(tab[i], tab[i + 1]);
			tab[i + 1] = ft_strcpy2(tab[i + 1], tmp);
			i = 0;
		}
		else
			i++;
	}
	free(tmp);
	return (tab);
}

char	**ft_sort_env(t_env *copy)
{
	char	**tab;
	char	*tmp;
	t_env	*tmp_env;
	int		i;

	tmp_env = copy;
	i = 0;
	tmp = malloc(sizeof(char) * 5000);
	ft_bzero(tmp, 5000);
	tab = malloc_the_tab(tmp_env);
	if (tab == NULL)
		return (NULL);
	while (copy)
	{
		tab[i] = malloc_the_str(copy);
		if (tab[i] == NULL)
			return ((char **)ft_free_tab(tab));
		copy = copy->next;
		i++;
	}
	return (sort_tab(tab, tmp));
}
