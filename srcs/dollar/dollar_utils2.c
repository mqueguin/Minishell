/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tale-fau <tale-fau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 14:59:54 by tale-fau          #+#    #+#             */
/*   Updated: 2022/02/28 15:19:18 by tale-fau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_for_redirect_dollar(t_token *token)
{
	return (ft_check_dollar(token->content) && token->prev
		&& ft_strncmp_check_len(token->prev->content, "<<", 2) == 0);
}

int	check_which_quotes(t_token *token)
{
	return (token->content && (token->content[0] == SINGLE_QUOTE
			|| token->content[0] == DOUBLE_QUOTE));
}
