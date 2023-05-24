/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_from_stdin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqueguin <mqueguin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 17:48:42 by tale-fau          #+#    #+#             */
/*   Updated: 2022/02/26 01:34:34 by mqueguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	read_from_stdin(char *prompt, t_env *env)
{
	char	*line;

	while (1)
	{
		line = display_prompt(prompt, env);
		if (line == NULL)
			return (FAILURE);
		add_history(line);
		parsing(line, &env);
		free(line);
	}
	return (SUCCESS);
}
