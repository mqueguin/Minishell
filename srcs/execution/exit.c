/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tale-fau <tale-fau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 14:58:18 by mqueguin          #+#    #+#             */
/*   Updated: 2022/02/28 15:13:43 by mqueguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_overflow(char *str)
{
	if (ft_strlen(str) > ft_strlen("9223372036854775807"))
		return (SUCCESS);
	if (ft_strncmp(str, "9223372036854775807", ft_strlen(str)) > 0)
		return (SUCCESS);
	return (FAILURE);
}

int	check_arg_is_digit(t_node *node, int i, int fork, int *j)
{
	int	ret;

	if (node->arg[0] && is_overflow(node->arg[0]) == SUCCESS)
	{
		if (fork)
			ft_putstr_fd("minishell: exit: numeric argument required\n",
				2);
		exit(255);
	}
	ret = 0;
	if (i >= 1)
	{
		if (!ft_isdigit(node->arg[0]))
		{
			if (fork)
			{
				ft_putstr_fd("minishell: exit: numeric argument required\n",
					2);
				*j = 1;
			}
			exit(255);
		}
		ret = ft_atoi(node->arg[0]);
	}
	return (ret);
}

int	exit_success(void)
{
	write(1, "\b\bexit\n", 7);
	return (SUCCESS);
}

int	cmd_exit(t_env *env, t_node *node, int fork, int i)
{
	int	ret;
	int	j;

	ret = 0;
	j = 0;
	if (node == NULL)
		exit(exit_success());
	while (node->arg[i])
		i++;
	ret = check_arg_is_digit(node, i, fork, &j);
	if (i > 1 && fork && j == 0)
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
	if (i > 1 && j == 0)
		return (FAILURE);
	if (!node->option && node->arg[0])
		exit(ft_atoi(node->arg[0]) % 256);
	else if (node->arg && node->arg[0])
		exit(ft_atoi(node->option) % 256);
	if (!node->next && !node->prev)
	{
		ft_free_env(env);
		free_node(node);
		exit(ft_atoi(g_status));
	}
	return (ret);
}
