/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tale-fau <tale-fau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 16:36:46 by tale-fau          #+#    #+#             */
/*   Updated: 2022/02/28 15:21:06 by tale-fau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	good_number_of_arg(int ac, char **av)
{
	if (ac != 1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(av[1], 2);
		ft_putstr_fd(": No such file or directory\n", 2);
	}
	return (ac != 1);
}

int	return_ret_status(char **ret_status, char *str)
{
	*ret_status = ft_strdup(str);
	return (FAILURE);
}

t_env	*handle_env(char **envp, t_env *env)
{
	if (!envp[0])
		return (NULL);
	env = NULL;
	env = copy_env(envp, 0);
	if (env == NULL)
		return (NULL);
	return (env);
}

int	handle_prompt(char **prompt, t_env *env)
{
	*prompt = set_prompt(env);
	if (!(*prompt))
	{
		*prompt = ft_strdup("minishell");
		if (*prompt == NULL)
			return (FAILURE);
	}
	return (SUCCESS);
}

int	main(int ac, char **av, char **envp)
{
	char		*prompt;
	t_env		*env;

	env = NULL;
	prompt = NULL;
	g_status = NULL;
	change_status("0");
	if (g_status == NULL)
		return (error(1));
	if (good_number_of_arg(ac, av) == FAILURE)
		return (FAILURE);
	(void)av;
	if (!handle_signal())
		return (error(13));
	env = handle_env(envp, env);
	if (env == NULL)
		return (error(8));
	if (handle_prompt(&prompt, env) == FAILURE)
		return (FAILURE);
	if (read_from_stdin(prompt, env) == FAILURE)
		return (FAILURE);
	free(prompt);
	free(g_status);
	g_status = NULL;
	return (SUCCESS);
}
