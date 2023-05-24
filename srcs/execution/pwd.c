/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tale-fau <tale-fau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 16:45:23 by mqueguin          #+#    #+#             */
/*   Updated: 2022/02/24 22:20:26 by tale-fau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	cmd_pwd(t_env *env)
{
	char	*pwd;
	t_env	*tmp;
	int		j;
	char	buf[5000];

	tmp = env;
	j = 0;
	getcwd(buf, 5000);
	write(1, buf, ft_strlen(buf));
	write(1, "\n", 1);
	return (SUCCESS);
	pwd = ft_strdup(env->env + j);
	if (pwd == NULL)
	{
		ft_putstr_fd("Minishell: Memory allocation failed\n", 2);
		return (FAILURE);
	}
	write(1, pwd, ft_strlen(pwd));
	write(1, "\n", 1);
	free(pwd);
	env = tmp;
	return (SUCCESS);
}
