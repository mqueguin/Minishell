/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_filler_utils.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqueguin <mqueguin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 05:02:41 by tale-fau          #+#    #+#             */
/*   Updated: 2022/02/28 02:09:22 by mqueguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	next_token_is_ok(t_token *token)
{
	return (token->next
		&& (ft_strncmp_check_len(token->next->content, ">", 1) == 0
			|| ft_strncmp_check_len(token->next->content, "<", 1) == 0
			|| ft_strncmp_check_len(token->next->content, ">>", 2) == 0
			|| ft_strncmp_check_len(token->next->content, "<<", 2) == 0
			|| ft_strncmp_check_len(token->next->content, "|", 1) == 0));
}

int	unexpected_quote_token(t_token *token, int **ret)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
	ft_putstr_fd(token->next->content, 2);
	ft_putstr_fd("'\n", 2);
	**ret = 1;
	change_status("258");
	return (FAILURE);
}

int	ft_redirection_filler(t_token *token, t_node **node,
		int type, int **ret)
{
	if (token->next && token->next->content && token->next->content[0] == '\0')
	{
		ft_putstr_fd("minishell: : No such file or directory\n",
			2);
		change_status("1");
		**ret = 1;
		return (FAILURE);
	}
	if (!token->next)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `newline'\n",
			2);
		change_status("258");
		**ret = 1;
		return (FAILURE);
	}
	else if (next_token_is_ok(token))
	{
		if (token->next->quote == 0)
			return (unexpected_quote_token(token, ret));
	}
	create_redirection_node(*node, token->next->content, type,
		token->next->quote);
	(*node)->nb_redirections += 1;
	return (SUCCESS);
}
