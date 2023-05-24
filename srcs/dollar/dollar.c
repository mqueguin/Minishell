/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqueguin <mqueguin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 14:51:49 by tale-fau          #+#    #+#             */
/*   Updated: 2022/02/28 00:45:39 by mqueguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*join_tab_and_return(char **tab, int count)
{
	int		i;
	char	*ret;

	i = 0;
	ret = NULL;
	while (i < count)
	{
		if (tab[i])
		{
			if (!ret)
				ret = ft_strdup(tab[i]);
			else
				ret = ft_strjoinfree(ret, tab[i]);
			i++;
		}
		else
			i++;
	}
	if (count < 2)
		return (ft_strdup(tab[0]));
	else
	{
		ft_free_tab(tab);
		return (ret);
	}
}

char	*question_mark_or_var_env(char **tab, int i, t_env *env)
{
	char	*ret;

	ret = NULL;
	if (tab[i][1] == '?')
	{
		tab[i] = transform_question_mark(tab[i]);
		if (tab[i] == NULL)
			return (ft_free_tab(tab));
	}
	else
	{
		ret = find_equivalent_with_name(env, tab[i] + 1);
		free(tab[i]);
		tab[i] = ft_strdup(ret);
		free(ret);
		if (tab[i] == NULL)
			return (ft_free_tab(tab));
	}
	return (tab[i]);
}

char	*lets_go_for_an_other_split(t_env *env, char *str, int count)
{
	char	**tab;
	char	*ret;
	int		i;

	i = 0;
	tab = ft_mini_split(str, DOLLAR);
	if (tab == NULL)
		return (NULL);
	while (tab[i])
	{
		if (tab[i][0] == DOLLAR)
			tab[i] = question_mark_or_var_env(tab, i, env);
		i++;
		count++;
	}
	ret = join_tab_and_return(tab, count);
	free(str);
	return (ret);
}

int	ft_check_dollar(char *content)
{
	while (*content)
	{
		if (*content == '$')
			return (1);
		content++;
	}
	return (0);
}

t_list_token	*manage_dollar(t_env *env, t_list_token *ls_tk)
{
	t_token	*token;

	token = ls_tk->front;
	while (token)
	{
		if (!token->prev && token->content
			&& token->content[0] == DOLLAR && token->content[1] != '?'
			&& !token->next)
			return (lonely_token(ls_tk, token, env));
		else
		{
			token = multiple_tokens(token, env);
			if (token == NULL)
				return (NULL);
		}
		fill_id(token);
		token = token->next;
	}
	return (ls_tk);
}
