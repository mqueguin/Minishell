/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_filler.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqueguin <mqueguin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 12:07:27 by tale-fau          #+#    #+#             */
/*   Updated: 2022/02/27 21:15:25 by mqueguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_arg_size(t_token *tmp)
{
	int	len;

	len = 0;
	while (tmp->content && tmp->id != PIPE_ID)
	{
		if (tmp->space == 0)
			len++;
		if (tmp->next)
			tmp = tmp->next;
		else
			break ;
	}
	return (len);
}

t_token	*cat_full_arg(char ***ret, t_token *token, int i, int j)
{
	while (token && token->id != PIPE_ID)
	{
		if (j == 0)
		{
			ret[0][i] = ft_strdup(token->content);
		}
		else if (j == 1)
		{
			ret[0][i] = ft_strjoin_free_str(ret[0][i], token->content, 1, 0);
		}
		if (token->next && token->next->space == 1)
		{
			j = 1;
			token = token->next;
		}
		else
		{
			i++;
			j = 0;
			token = token->next;
		}
	}
	return (token);
}

char	**malloc_full_arg_size(t_token *token)
{
	int		len;
	t_token	*tmp;

	tmp = token;
	len = 0;
	if (tmp)
		len = get_arg_size(tmp);
	return (malloc_arg_and_return(len));
}

t_token	*get_full_arg(t_token *token, char ***ret)
{
	free(*ret);
	*ret = malloc_full_arg_size(token);
	if (*ret == NULL)
		return (NULL);
	if (token)
		token = cat_full_arg(ret, token, 0, 0);
	return (token);
}

t_token	*arg_filler(t_token *token, char ***arg)
{
	token = get_full_arg(token, arg);
	if (token == NULL)
		return (NULL);
	return (token);
}
