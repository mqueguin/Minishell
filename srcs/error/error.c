/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tale-fau <tale-fau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 18:04:09 by tale-fau          #+#    #+#             */
/*   Updated: 2022/02/27 17:56:11 by tale-fau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	bad_command_return(char	*str)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": command not found\n", 2);
	return (FAILURE);
}

int	ft_strerror(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		write(2, &str[i], 1);
	return (FAILURE);
}

t_env	*error_malloc_t_env(t_env *env, int i)
{
	if (i == 1)
		ft_free_env(env);
	ft_putstr_fd("minishell: Memory allocation failed\n", 2);
	return (NULL);
}

char	*error_malloc_char(void)
{
	ft_putstr_fd("minishell: Memory allocation failed\n", 2);
	return (NULL);
}

int	error(int id)
{
	static char	*str[14] = {"minishell: Wrong number of arguments.\n",
		"minsihell: Dynamic allocation issue.\n",
		"minishell: Failed to fork program\n",
		"minishell: Unspecified special character found in command line.\n",
		"minsihell: Mandatory input after a pipe.\n",
		"minishell: Syntax error near unexpected token `|'.\n",
		"minishell: Not printable character in entry line.\n",
		"minishell: Too many options !\n",
		"minishell: invalid environment.\n",
		"minishell: invalid number of single quotes.\n",
		"minishell: invalid number of double quotes.\n",
		"minishell: command line too big for minishell to handle.\n",
		"minishell: unset: `\": not a valid identifier\n",
		"minishell: signal error\n"};

	if (id == 5)
	{
		free(g_status);
		g_status = ft_strdup("258");
	}
	return (ft_strerror(str[id]));
}
