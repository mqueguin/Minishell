/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tale-fau <tale-fau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 19:15:55 by tale-fau          #+#    #+#             */
/*   Updated: 2022/02/08 13:55:41 by tale-fau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*delete_element(t_token *token)
{
	t_token	*tmp;
	t_token	*previous;

	if (token == NULL)
		return (token);
	previous = token;
	tmp = previous->next;
	while (tmp)
	{
		if (tmp->space == 1 && (ft_strlen(tmp->content) == 0))
		{
			previous->next = tmp->next;
			free(tmp);
			return (token);
		}
		previous = tmp;
		tmp = tmp->next;
	}
	return (token);
}

t_token	*find_empty_token(t_list_token *ls_tk)
{
	t_token	*token;

	token = ls_tk->front;
	token = delete_element(token);
	return (token);
}

int	is_there_dollar_question_mark(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == DOLLAR && str[i + 1] == '?')
			return (SUCCESS);
		i++;
	}
	return (FAILURE);
}
