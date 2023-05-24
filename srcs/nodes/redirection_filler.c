/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_filler.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tale-fau <tale-fau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 18:49:53 by mqueguin          #+#    #+#             */
/*   Updated: 2022/02/28 15:00:57 by tale-fau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_token_and_token_next(t_token *token)
{
	if (token->next)
		free_token(token->next);
	if (token)
		free_token(token);
}

t_token	*erase_token_exec(t_token *token, t_file **file, t_token *prev)
{
	if (ft_strncmp_check_len(token->next->content, (*file)->path,
			ft_strlen((*file)->path)) == SUCCESS && token->next->next)
	{
		if (token->prev)
		{
			token->prev->next = token->next->next;
			token->next->next->prev = token->prev;
			free_token_and_token_next(token);
		}
		else if (!token->prev)
		{
			token = token->next->next;
			token->prev = NULL;
			free_token_and_token_next(token);
			return (token);
		}
	}
	else if (ft_strncmp_check_len(token->next->content, (*file)->path,
			ft_strlen((*file)->path)) == SUCCESS && !token->next->next)
	{
		if (token->prev)
			token->prev->next = NULL;
		free_token_and_token_next(token);
	}
	return (prev);
}

t_token	*ft_erase_redirection_token(t_token *token, t_file *file)
{
	while (token)
	{
		if (file->type == 0
			&& ft_strncmp_check_len(token->content, ">", 1) == SUCCESS)
			return (erase_token_exec(token, &file, token->prev));
		else if (file->type == 1
			&& ft_strncmp(token->content, "<", 1) == SUCCESS)
			return (erase_token_exec(token, &file, token->prev));
		else if (file->type == 2
			&& (ft_strncmp_check_len(token->content, ">>",
					ft_strlen(file->path)) == SUCCESS))
			return (erase_token_exec(token, &file, token->prev));
		else if (file->type == 3
			&& (ft_strncmp_check_len(token->content, "<<",
					ft_strlen(file->path)) == SUCCESS))
			return (erase_token_exec(token, &file, token->prev));
		if (token->next)
			token = token->next;
		else
			break ;
	}
	return (token);
}

int	ft_is_quoting_ok(t_token *token, t_node **node, int *ret)
{
	if (ft_strncmp_check_len(token->content, ">", 1) == SUCCESS)
		if (ft_redirection_filler(token, node, 0, &ret) == FAILURE)
			return (FAILURE);
	if (ft_strncmp_check_len(token->content, "<", 1) == SUCCESS)
		if (ft_redirection_filler(token, node, 1, &ret) == FAILURE)
			return (FAILURE);
	if (ft_strncmp_check_len(token->content, ">>", 2) == SUCCESS)
		if (ft_redirection_filler(token, node, 2, &ret) == FAILURE)
			return (FAILURE);
	if (ft_strncmp_check_len(token->content, "<<", 2) == SUCCESS)
		if (ft_redirection_filler(token, node, 3, &ret) == FAILURE)
			return (FAILURE);
	return (SUCCESS);
}

int	ft_check_token(t_token *token, t_node **node, int *ret, t_list *ls)
{
	while (token)
	{
		if (token->content[0] == '|' && token->id == PIPE_ID)
		{
			add_tail(ls);
			(*node) = (*node)->next;
		}
		if (token->quote == 0)
			if (ft_is_quoting_ok(token, node, ret) == FAILURE)
				return (FAILURE);
		if (token->next)
			token = token->next;
		else
			break ;
	}
	return (SUCCESS);
}
