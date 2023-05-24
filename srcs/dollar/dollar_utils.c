/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tale-fau <tale-fau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 17:14:15 by tale-fau          #+#    #+#             */
/*   Updated: 2022/02/28 15:18:56 by tale-fau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*split_and_send_to_replace(t_env *env, char *str, int count)
{
	int		i;
	char	**tab;
	char	*ret;

	i = 0;
	tab = ft_split_not_erase_sep(str, 0, 0);
	if (tab == NULL)
		return (NULL);
	while (tab[i])
	{
		if (check_dollar(tab[i]) == SUCCESS)
		{
			tab[i] = lets_go_for_an_other_split(env, tab[i], 0);
			if (tab[i] == NULL)
				return (NULL);
		}
		i++;
		count++;
	}
	ret = join_tab_and_return(tab, count);
	return (ret);
}

char	*handle_dollar(char *str, t_env *env)
{
	char		*ret;

	ret = NULL;
	str = need_to_remove_quotes(str);
	if (!str)
		return (NULL);
	if (str && (check_dollar(str) == SUCCESS))
	{
		ret = split_and_send_to_replace(env, str, 0);
		if (ret == NULL)
			return (NULL);
	}
	else
		return (str);
	if (str)
		free(str);
	return (ret);
}

int	specific_check_for_specific_test(t_token *token)
{
	return (token->content && token->space == 0 && token->content[0] == '$'
		&& !token->content[1] && token->next
		&& token->next->content && token->next->space == 1);
}

t_token	*multiple_tokens(t_token *token, t_env *env)
{
	if (specific_check_for_specific_test(token))
	{
		free(token->content);
		token->content = ft_strdup("\0");
		if (token->content == NULL)
			return (NULL);
	}
	if (check_which_quotes(token))
		token->quote = 1;
	if (token->content && token->content[0] != SINGLE_QUOTE)
	{
		if (check_for_redirect_dollar(token) || check_dollar(token->content))
			token->content = need_to_remove_quotes(token->content);
		else if (token->content && check_dollar(token->content) == SUCCESS)
			token->content = handle_dollar(token->content, env);
		if (!token->content)
			return (NULL);
	}
	else
	{
		token->content = need_to_remove_quotes(token->content);
		if (!token->content)
			return (NULL);
	}
	return (token);
}
