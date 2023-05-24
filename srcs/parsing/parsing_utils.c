/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqueguin <mqueguin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 16:40:52 by tale-fau          #+#    #+#             */
/*   Updated: 2022/02/28 01:57:07 by mqueguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	return_status_success(void)
{
	if (g_status)
		free(g_status);
	g_status = ft_strdup("0");
	return (SUCCESS);
}

int	is_envp_empty(t_env *env)
{
	if (!env)
		return (error(8));
	else
		return (SUCCESS);
}
