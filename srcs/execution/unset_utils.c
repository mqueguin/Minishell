/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqueguin <mqueguin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 14:37:47 by tale-fau          #+#    #+#             */
/*   Updated: 2022/02/24 21:34:23 by mqueguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	suite(int fork, char *arg)
{		
	if (fork == 1)
	{
		ft_putstr_fd("minishell: export: `", 2);
		ft_putstr_fd(arg, 2);
		ft_putstr_fd("\': not a valid identifier\n", 2);
	}
	return (FAILURE);
}

int	ft_check_is_alpha_or_num(char c, char *arg, int y, int fork)
{
	if (y == 1)
	{
		if (!(c >= 'A' && c <= 'Z') && !(c >= 'a' && c <= 'z')
			&& !(c >= '0' && c <= '9'))
			return (SUCCESS);
	}
	else if (y == 2)
	{
		if (fork == 1)
		{
			ft_putstr_fd("minishell: unset: \'", 2);
			ft_putstr_fd(arg, 2);
			ft_putstr_fd("\': not a valid identifier\n", 2);
		}
		return (FAILURE);
	}
	else if (y == 3)
		return (suite(fork, arg));
	return (FAILURE);
}
