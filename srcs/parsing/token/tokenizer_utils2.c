/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqueguin <mqueguin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 17:16:13 by mqueguin          #+#    #+#             */
/*   Updated: 2022/02/27 23:27:23 by mqueguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*create_token_with_content(int content_size)
{
	t_token	*new;

	new = (t_token *)malloc(sizeof(t_token));
	if (new == NULL)
		return (NULL);
	init_node_token(new);
	new->content = (char *)malloc(sizeof(char) * content_size + 1);
	if (new->content == NULL)
		return (NULL);
	return (new);
}

t_token	*create_token_with_quote(char **str, int state)
{
	t_token	*new;
	int		i;
	char	quote_type;

	i = 1;
	quote_type = (*str)[0];
	while ((*str)[i] && (*str)[i] != quote_type)
		i++;
	new = create_token_with_content(++i);
	if (new == NULL)
		return (NULL);
	ft_strncpy(new->content, *str, i);
	if (state == 2)
		new->space = 1;
	*str = &((*str)[i]);
	return (new);
}

t_token	*create_token_without_quote(char **str, int state)
{
	t_token	*new;
	int		i;

	i = 0;
	while ((*str)[i] && (*str)[i] != SINGLE_QUOTE && (*str)[i] != DOUBLE_QUOTE)
		i++;
	new = create_token_with_content(i);
	if (new == NULL)
		return (NULL);
	ft_strncpy(new->content, *str, i);
	if (state == 2)
		new->space = 1;
	*str = &((*str)[i]);
	return (new);
}

int	ft_assign_value_for_var_is_quote(t_data data, char *str)
{
	if (str[data.i] == SINGLE_QUOTE)
		data.is_quote = 1;
	else
		data.is_quote = 2;
	return (data.is_quote);
}

int	ft_tokenizer_error(int err)
{
	if (err == 0)
		ft_putstr_fd("minishell: parsing: quotes error\n", 2);
	return (FAILURE);
}
