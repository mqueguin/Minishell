/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lonely_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqueguin <mqueguin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 02:30:07 by tale-fau          #+#    #+#             */
/*   Updated: 2022/02/27 18:59:53 by mqueguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list_token	*lonely_token(t_list_token *ls_tk, t_token *token, t_env *env)
{
	char	*ret;

	ret = find_equivalent_with_name(env, token->content + 1);
	free(token->content);
	token->content = ft_strdup(ret);
	free(ret);
	if (token->content && !token->content[0])
	{
		if (g_status)
			free(g_status);
		g_status = ft_strdup("0");
		return (NULL);
	}
	return (ls_tk);
}
