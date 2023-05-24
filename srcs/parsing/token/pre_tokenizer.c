/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_tokenizer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqueguin <mqueguin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 18:07:51 by tale-fau          #+#    #+#             */
/*   Updated: 2022/02/28 00:21:25 by mqueguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	result_loop_tokenizer(t_data *data, t_token *token, char *str,
	t_list_token *ls_token)
{
	if (token->content != NULL && token->next->content != NULL)
	{
		if (!reading_loop(&str[data->i], token->next->next, ls_token))
			return (0);
	}
	else if (token->content != NULL && token->next->content == NULL)
	{
		if (!reading_loop(&str[data->i], token->next, ls_token))
			return (0);
	}
	else if (token->content == NULL)
	{
		if (!reading_loop(&str[data->i], token, ls_token))
			return (0);
	}
	return (1);
}

int	check_return_value_of_tokenizer(t_data *data, t_token *token,
	char *str, t_list_token *ls_token)
{
	int	j;

	j = 0;
	if (ft_strlen(data->buf) > 0)
		if (fill_content(data->buf, token, &str[data->i], ls_token) == FAILURE)
			return (FAILURE);
	if (str[data->i] == '\0')
		return (SUCCESS);
	if (data->sep_id > 0)
		if (content_null_or_not(token, data, ls_token, str) == FAILURE)
			return (FAILURE);
	if (data->is_quote == 0)
	{
		j = skip_spaces(&str[data->i]);
		if (str[data->i + j] == '\0')
			return (SUCCESS);
	}
	if (str[data->i] == '\0')
		return (SUCCESS);
	return (FAILURE);
}

int	ft_check_quotes_error(t_data *data, char *str)
{
	int	j;

	j = 0;
	if (data->is_quote > 0)
		return (ft_tokenizer_error(0));
	if (str[data->i] == SPACE)
	{
		j = skip_spaces(&str[data->i]);
		if (str[data->i + j] == SINGLE_QUOTE
			|| str[data->i + j] == DOUBLE_QUOTE)
		{
			if (str[data->i + (j + 1)] == '\0')
				return (ft_tokenizer_error(0));
			else if (str[data->i + (j + 1)] == SPACE)
			{
				j++;
				while (str[data->i + j] == SPACE)
					j++;
				if (str[data->i + j] == '\0')
					return (ft_tokenizer_error(0));
			}
		}
	}
	return (SUCCESS);
}

int	reading_loop(char *str, t_token *token, t_list_token *ls_token)
{
	t_data	data;

	ft_init_data(&data);
	while (str[data.i] && ft_check_is_sep(str, &data) == 0)
	{
		if (str[data.i] == SINGLE_QUOTE || str[data.i] == DOUBLE_QUOTE)
		{
			if (data.is_quote == 0)
				data.is_quote = ft_assign_value_for_var_is_quote(data, str);
			else if ((str[data.i] == SINGLE_QUOTE && data.is_quote == 1)
				|| (str[data.i] == DOUBLE_QUOTE && data.is_quote == 2))
				data.is_quote = 0;
		}
		if (!fill_buffer_and_check_multiple_dollar(&data, str))
			return (FAILURE);
	}
	if (ft_check_quotes_error(&data, str) == FAILURE)
		return (FAILURE);
	if (check_return_value_of_tokenizer(&data, token, str, ls_token) == SUCCESS)
		return (SUCCESS);
	if (!result_loop_tokenizer(&data, token, str, ls_token))
		return (SUCCESS);
	return (FAILURE);
}

t_list_token	*init_read_through_str(char *str, t_list_token *ls_token)
{
	t_token			*token;

	ls_token = add_front(ls_token);
	if (ls_token == NULL)
		return (NULL);
	token = ls_token->front;
	if (reading_loop(str, token, ls_token) == FAILURE)
		return (NULL);
	if (token_handler(ls_token) == FAILURE)
		return (NULL);
	return (ls_token);
}
