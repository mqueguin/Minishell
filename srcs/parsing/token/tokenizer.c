/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqueguin <mqueguin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 12:18:41 by tale-fau          #+#    #+#             */
/*   Updated: 2022/02/28 00:16:38 by mqueguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	fill_id_suite(t_token *token)
{
	if (!token->prev || token->prev->id == PIPE_ID)
		token->id = CMD;
	else if (token->prev->id == CMD && token->space == 1)
		token->id = CMD;
	else if ((token->prev->id == CMD || token->prev->id == PIPE_ID)
		&& token->content[0] == DASH && token->content[1]
		&& token->content[1] != SPACE)
		token->id = OPTION;
	else if (token->prev->id == OPTION && token->space == 1)
		token->id = OPTION;
	else if (token->prev->id == OPTION && token->content[0] == DASH
		&& token->content[1] && token->space == 0)
		token->id = OPTION;
	else
		token->id = ARG;
}

void	fill_id(t_token *token)
{
	if (token->content[0] == PIPE && token->pipe_in_quote == 0)
		token->id = PIPE_ID;
	else if (token->content[0] == LEFT_ARROW)
	{
		if (token->content[1] == LEFT_ARROW)
			token->id = DBL_LEFT_ARR;
		else
			token->id = LEFT_ARR;
	}
	else if (token->content[0] == RIGHT_ARROW)
	{
		if (token->content[1] == RIGHT_ARROW)
			token->id = DBL_RIGHT_ARR;
		else
			token->id = RIGHT_ARR;
	}
	else
		fill_id_suite(token);
}

static int	check_if_pipe_is_in_quote(char *str)
{
	int		i;
	char	quote;

	i = 0;
	quote = 0;
	if (str[i] == SINGLE_QUOTE)
		quote = SINGLE_QUOTE;
	else if (str[i] == DOUBLE_QUOTE)
		quote = DOUBLE_QUOTE;
	else
		return (0);
	i++;
	while (str[i] && str[i] != quote)
	{
		if (str[i] == PIPE)
			return (1);
		i++;
	}
	return (0);
}

int	fill_content(char *buf, t_token *token, char *str,
	t_list_token *ls_token)
{
	token->content = ft_strdup(buf);
	if (token->content == NULL)
		return (FAILURE);
	token->pipe_in_quote = check_if_pipe_is_in_quote(token->content);
	if (token->content[0] != '|')
	{
		token->content = manage_quotes(token->content);
		if (token->content == NULL)
			return (FAILURE);
	}
	while (*str == SPACE)
		str++;
	if (*str != '\0')
	{
		ls_token = add_back(ls_token);
		if (ls_token == NULL)
			return (FAILURE);
	}
	return (SUCCESS);
}
