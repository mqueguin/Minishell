/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cloning.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqueguin <mqueguin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 17:06:31 by tale-fau          #+#    #+#             */
/*   Updated: 2022/02/28 13:57:21 by mqueguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*clone_zer(char *line, char *ret, int *i, int *j)
{
	if (i != 0 && line[*i + 1])
	{
		if (line[*i] == PIPE && line[*i - 1] != SPACE)
		{
			ret[*j] = SPACE;
			*j += 1;
		}
	}
	ret[*j] = line[*i];
	*j += 1;
	if (i != 0 && line[*i + 1])
	{
		if (line[*i] == PIPE && line[*i + 1] != SPACE)
		{
			ret[*j] = SPACE;
			*j += 1;
		}
	}
	return (ret);
}

char	*clone_str(char *ret, char *line, int *len_pipes)
{
	int	i;
	int	j;
	int	number_pipes;

	i = 0;
	j = 0;
	number_pipes = 0;
	while (line[i])
	{
		if (line[i] == PIPE && len_pipes[number_pipes++] == 0)
			ret = clone_zer(line, ret, &i, &j);
		else if (line[i] == '	')
			ret[j++] = SPACE;
		else
			ret[j++] = line[i];
		i++;
	}
	return (ret);
}

int	error_quotes(int i)
{
	if (i == 1)
		return (error(9));
	if (i == 2)
		return (error(10));
	return (FAILURE);
}

int	search_for_quotes(char *line)
{
	int	i;
	int	s_count;
	int	d_count;

	s_count = 0;
	d_count = 0;
	i = -1;
	while (line[++i])
	{
		if (line[i] == SINGLE_QUOTE)
			s_count++;
		else if (line[i] == DOUBLE_QUOTE)
			d_count++;
	}
	if (s_count % 2 != SUCCESS)
		return (error_quotes(1));
	if (d_count % 2 != SUCCESS)
		return (error_quotes(2));
	return (SUCCESS);
}

char	*cloning(char *line)
{
	char	*ret;
	int		total_len;
	int		*len_pipes;

	len_pipes = check_number_of_pipe_into_quotes(line, 0, 0);
	if (len_pipes == NULL)
		return (NULL);
	total_len = parse_pipes(line, -1, 0, len_pipes);
	if (total_len == -42)
	{
		free(len_pipes);
		return (NULL);
	}
	ret = (char *)malloc(sizeof(char) * (total_len + 1));
	if (ret == NULL)
	{
		free(len_pipes);
		return (NULL);
	}
	ret[total_len] = '\0';
	ret = clone_str(ret, line, len_pipes);
	free(len_pipes);
	return (ret);
}
