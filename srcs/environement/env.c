/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tale-fau <tale-fau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 11:31:11 by mqueguin          #+#    #+#             */
/*   Updated: 2022/02/27 15:47:21 by tale-fau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cmd_env(t_env *env)
{
	if (env == NULL || env->env == NULL)
		return (SUCCESS);
	ft_display_env(env);
	return (SUCCESS);
}
