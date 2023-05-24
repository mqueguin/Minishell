/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqueguin <mqueguin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 12:09:45 by mqueguin          #+#    #+#             */
/*   Updated: 2022/02/27 22:14:33 by mqueguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strjoin_one_char(char *s1, char c)
{
	char	*ret;
	int		i;

	i = -1;
	ret = malloc(sizeof(char) * (ft_strlen(s1) + 2));
	if (ret == NULL)
	{
		if (s1)
			free(s1);
		return (error_malloc_char());
	}
	if (!s1)
	{
		ret[0] = c;
		ret[1] = '\0';
	}
	else
	{
		while (s1[++i])
			ret[i] = s1[i];
		ret[i++] = c;
		ret[i] = '\0';
		free(s1);
	}
	return (ret);
}

void	wait_function(int pid)
{
	int		status;
	char	*tmp;

	waitpid(pid, &status, 0);
	tmp = NULL;
	if (WIFEXITED(status) == 1)
	{
		tmp = ft_itoa(WEXITSTATUS(status));
		change_status(tmp);
	}
	else if (WIFSIGNALED(status) == 1)
	{
		tmp = ft_itoa(128 + WTERMSIG(status));
		change_status(tmp);
	}
	if (tmp)
		free(tmp);
}

static char	*create_file_name(char *name, int nb)
{
	char	*tmp;
	char	*nbr;
	char	*ret;

	tmp = ft_strdup(name);
	if (tmp == NULL)
		return (NULL);
	nbr = ft_itoa(nb);
	if (nbr == NULL)
	{
		free(tmp);
		return (NULL);
	}
	ret = ft_strjoin(tmp, nbr);
	free(tmp);
	free(nbr);
	return (ret);
}

char	*create_file_name_heredoc(char *name)
{
	int		i;
	char	*ret;

	i = -1;
	if (access(name, F_OK) != 0)
		return (ft_strdup(name));
	while (++i <= 10000)
	{
		ret = create_file_name(name, i);
		if (ret == NULL)
			return (NULL);
		if (access(ret, F_OK) != 0)
			return (ret);
		free(ret);
	}
	return (NULL);
}
