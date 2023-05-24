/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqueguin <mqueguin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 15:50:27 by mqueguin          #+#    #+#             */
/*   Updated: 2022/02/26 02:02:26 by mqueguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*free_dup_content(char *buf, char **content)
{
	free(*content);
	*content = ft_strdup(buf);
	return (*content);
}

void	ft_init_data(t_data *data)
{
	data->i = 0;
	data->j = 0;
	ft_bzero(data->buf, 1000);
	data->is_quote = 0;
}

int	ft_check_is_sep(char *str, t_data *data)
{
	if (str[data->i] == ' ' && data->is_quote == 0)
		data->sep_id = 1;
	else if (str[data->i] == '|' && data->is_quote == 0)
		data->sep_id = 2;
	else if (str[data->i] == '<' && str[data->i + 1] == '<'
		&& data->is_quote == 0)
		data->sep_id = 3;
	else if (str[data->i] == '<' && data->is_quote == 0)
		data->sep_id = 4;
	else if (str[data->i] == '>' && str[data->i + 1] == '>'
		&& data->is_quote == 0)
		data->sep_id = 5;
	else if (str[data->i] == '>' && data->is_quote == 0)
		data->sep_id = 6;
	else if (str[data->i] == '\0')
		data->sep_id = -1;
	else
		data->sep_id = 0;
	return (data->sep_id);
}

int	ft_fill_sep_next_part(t_data *data, t_token *token,
		char *str, t_list_token *ls_token)
{
	if (data->sep_id == 4)
	{
		data->i++;
		if (fill_content("<", token, &str[data->i], ls_token) == FAILURE)
			return (FAILURE);
	}
	else if (data->sep_id == 5)
	{
		data->i += 2;
		if (fill_content(">>", token, &str[data->i], ls_token) == FAILURE)
			return (FAILURE);
	}
	else if (data->sep_id == 6)
	{
		data->i++;
		if (fill_content(">", token, &str[data->i], ls_token) == FAILURE)
			return (FAILURE);
	}
	return (SUCCESS);
}

int	fill_buffer_and_check_multiple_dollar(t_data *data, char *str)
{
	if (str[data->i] == '$' && str[data->i + 1] == '$' && data->is_quote == 0)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token '$'\n", 2);
		return (0);
	}
	if (str && str[data->i])
	{
		data->buf[data->j++] = str[data->i++];
		data->buf[data->j] = '\0';
	}
	return (1);
}
