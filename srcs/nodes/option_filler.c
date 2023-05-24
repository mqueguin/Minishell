/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   option_filler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tale-fau <tale-fau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 13:38:36 by tale-fau          #+#    #+#             */
/*   Updated: 2022/02/24 21:00:04 by tale-fau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_option_size(t_token *tmp)
{
	int	len;

	len = 0;
	while (tmp && (tmp->id == OPTION))
	{
		if (len > 0 && tmp->space == 0)
			len++;
		len += ft_strlen(tmp->content);
		if (tmp->next && tmp->next->content)
			tmp = tmp->next;
		else
			break ;
	}
	return (len);
}

t_token	*cat_full_option(char **ret, t_token *token)
{
	while (token && (token->id == OPTION))
	{
		*ret = ft_strcat_quote(*ret, token->content, token->quote);
		if (token->next && token->next->content)
		{
			if (token->next->id == OPTION && token->next->space == 0)
			{
				*ret = ft_strcat(*ret, " ");
			}
			token = token->next;
		}
		else
			break ;
	}
	return (token);
}

char	*malloc_full_size(t_token *token)
{
	int		len;
	t_token	*tmp;

	tmp = token;
	len = 0;
	if (token->id == OPTION || token->content[0] == DASH)
	{
		len = get_option_size(tmp);
	}
	return (malloc_and_return(len));
}

t_token	*get_full_option(t_token *token, char **ret)
{
	*ret = malloc_full_size(token);
	if (*ret == NULL)
		return (NULL);
	if (token->id == OPTION || token->content[0] == DASH)
		token = cat_full_option(ret, token);
	return (token);
}

t_token	*option_filler(t_token *token, char **ret, int **i)
{
	(void)i;
	token = get_full_option(token, ret);
	if (*ret == NULL)
		return (NULL);
	if (token == NULL)
		return (NULL);
	if ((token->content && token->content[0] == DASH
			&& token->content[1] && token->content[1] != SPACE)
		|| (token && token->space == 1))
		**i = 2;
	return (token);
}
