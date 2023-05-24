/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqueguin <mqueguin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 16:10:34 by tale-fau          #+#    #+#             */
/*   Updated: 2022/02/28 14:22:11 by mqueguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clear_both_lists(t_list_token *ls_token, t_list *t_list_node)
{
	clear_list_token(ls_token);
	clear_list(t_list_node);
}

int	pre_checks(char **line, t_env *env)
{
	(void)env;
	if (**line == '\0')
		return (FAILURE);
	while (**line)
	{
		if (**line != SPACE)
			break ;
		(*line)++;
	}
	if (**line == '\0')
		return (FAILURE);
	return (SUCCESS);
}

int	parsing_suite(t_list_token *ls_token, t_env **env, t_list *t_list_node)
{
	ls_token = manage_dollar(*env, ls_token);
	if (ls_token == NULL)
	{
		clear_list_token(ls_token);
		return (FAILURE);
	}
	t_list_node = manage_nodes(ls_token, t_list_node);
	if (t_list_node == NULL)
	{
		clear_both_lists(ls_token, t_list_node);
		return (FAILURE);
	}
	if (ft_start_execution(env, t_list_node, 0) == FAILURE)
		return (FAILURE);
	clear_list(t_list_node);
	return (SUCCESS);
}

int	parsing(char *line, t_env **env)
{
	char			*clone;
	t_list_token	*ls_token;
	t_list			*t_list_node;

	ls_token = NULL;
	t_list_node = NULL;
	if (pre_checks(&line, *env) == FAILURE)
	{
		if (line[0])
		{
			free(g_status);
			g_status = ft_strdup("258");
		}
		return (FAILURE);
	}
	clone = cloning(line);
	if (clone == NULL)
		return (FAILURE);
	ls_token = init_read_through_str(clone, ls_token);
	free(clone);
	if (ls_token == NULL)
		return (FAILURE);
	if (parsing_suite(ls_token, env, t_list_node) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}
