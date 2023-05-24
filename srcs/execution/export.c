/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tale-fau <tale-fau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/30 22:21:47 by mqueguin          #+#    #+#             */
/*   Updated: 2022/02/27 16:44:10 by tale-fau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strcpy2(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s2[i])
	{
		s1[i] = s2[i];
		i++;
	}
	s1[i] = '\0';
	return (s1);
}

int	ft_print_env_sorted(t_env *env, int fork)
{
	int		i;
	int		j;
	char	**tab;

	if (!fork)
		return (FAILURE);
	tab = ft_sort_env(env);
	i = 0;
	j = 0;
	while (tab[i])
	{
		j = 0;
		ft_putstr_fd("declare -x ", 1);
		while (tab[i][j] != '=')
			write(1, &tab[i][j++], 1);
		write(1, "=\"", 2);
		while (tab[i][++j])
			write(1, &tab[i][j], 1);
		write(1, "\"\n", 2);
		i++;
	}
	ft_free_tab(tab);
	return (SUCCESS);
}

int	ft_search_equal_char(char *str)
{
	while (*str)
	{
		if (*str == '=')
			return (SUCCESS);
		str++;
	}
	return (FAILURE);
}

int	cmd_export(t_node *node, t_env **env, int fork, int i)
{
	int		ret;

	if (*env == NULL && (!node->arg || !node->arg[0]))
		return (FAILURE);
	else if (*env == NULL && node->arg && node->arg[0])
	{
		(*env) = (t_env *)malloc(sizeof(t_env));
		(*env)->env = NULL;
		(*env)->next = NULL;
	}
	ret = 0;
	if ((*env)->env && node->option == NULL && node->arg[0] == NULL)
		return (ft_print_env_sorted(*env, fork));
	if (node->option)
		ret = ft_check_args(node->option, fork, -1, -1);
	while (node->arg[++i])
	{
		if (ft_check_args(node->arg[i], fork, -1, -1) == SUCCESS)
			with_good_args(node->arg[i], env);
		else
			ret = 1;
	}
	return (ret);
}
