/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_filler.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tale-fau <tale-fau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 14:29:06 by tale-fau          #+#    #+#             */
/*   Updated: 2022/02/25 02:15:51 by tale-fau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_cmd_size(t_token *tmp)
{
	int	len;

	len = 0;
	while (tmp && tmp->id == CMD)
	{
		len += ft_strlen(tmp->content);
		if (tmp->next && tmp->next->content)
			tmp = tmp->next;
		else
			break ;
	}
	return (len);
}

t_token	*cat_full_cmd(char **ret, t_token *token)
{
	while (token && token->id == CMD)
	{
		*ret = ft_strcat(*ret, token->content);
		if (token->next && token->next->content)
			token = token->next;
		else
			break ;
	}
	return (token);
}

char	*malloc_full_cmd_size(t_token *token)
{
	int		len;
	t_token	*tmp;

	tmp = token;
	len = 0;
	if (tmp->id == CMD)
		len = get_cmd_size(tmp);
	return (malloc_and_return(len));
}

t_token	*get_full_cmd(t_token *token, char **ret)
{
	*ret = malloc_full_cmd_size(token);
	if (*ret == NULL)
		return (NULL);
	if (token->id == CMD)
		token = cat_full_cmd(ret, token);
	return (token);
}

t_token	*cmd_filler(t_token *token, char **ret, int **i)
{
	token = get_full_cmd(token, ret);
	if (token == NULL)
		return (NULL);
	if (*ret == NULL)
		return (NULL);
	if (token && token->content && token->id == CMD)
		**i = 2;
	return (token);
}
