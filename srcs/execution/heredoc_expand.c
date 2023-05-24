/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_expand.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tale-fau <tale-fau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 15:25:02 by mqueguin          #+#    #+#             */
/*   Updated: 2022/02/27 17:54:03 by tale-fau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_recover_identifier(char *str, int end)
{
	char	*identifier;
	int		i;

	i = 0;
	identifier = malloc(sizeof(char) * (end + 1));
	if (identifier == NULL)
		return (error_malloc_char());
	identifier[end] = '\0';
	while (i < end)
	{
		identifier[i] = str[i];
		i++;
	}
	return (identifier);
}

static char	*ft_find_var_in_env(char *str, int end, t_env *env, int *status)
{
	char	*identifier;
	int		i;
	char	*ret;

	ret = NULL;
	i = 0;
	identifier = ft_recover_identifier(str, end);
	if (identifier == NULL)
		return (NULL);
	i = 0;
	env = find_index_in_env(env, &i, identifier);
	if (env == NULL)
	{
		free(identifier);
		return (NULL);
	}
	ret = ft_strdup(env->env + i);
	if (ret == NULL)
	{
		*status = 2;
		free(identifier);
		return (error_malloc_char());
	}
	return (ret);
}

static char	*ft_expand_var(char *str, int *i, t_env *env, int *status)
{
	char	*ret;
	int		copy_i;

	if (str[*i] == '$' && str[*i + 1] == '?')
	{
		free(g_status);
		ret = ft_strdup(g_status);
		if (ret == NULL)
			return (error_malloc_char());
		*i += 2;
		return (ret);
	}
	*i += 1;
	copy_i = 1;
	while (str[copy_i] && ((ft_isalnum_spe(str[copy_i])
				&& str[copy_i] != '$') || str[copy_i] == '_'))
		copy_i++;
	ret = ft_find_var_in_env(&str[1], copy_i - 1, env, status);
	if (ret == NULL && *status == 2)
		return (NULL);
	*i += copy_i - 1;
	return (ret);
}

static int	ft_expand_and_join(char **ret, char *line, int *i, t_env *env)
{
	int		end;
	char	*str;
	int		status;

	end = 0;
	status = 0;
	str = ft_expand_var(&line[*i], &end, env, &status);
	if (str == NULL && status == 2)
	{
		free(*ret);
		return (-1);
	}
	*ret = ft_strjoin_null(*ret, str, 0);
	if (*ret == NULL)
	{
		free(str);
		return (-1);
	}
	*i += end;
	free(str);
	return (1);
}

char	*ft_loop_expand(char *line, int count, char *ret, t_env *env)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if ((line[i] == '$' && ft_isalpha(line[i + 1]))
			|| (line[i] == '$' && line[i + 1] == '?'))
		{
			count = ft_expand_and_join(&ret, line, &i, env);
			if (count == -1)
				return (NULL);
		}
		else
		{
			ret = ft_strjoin_one_char(ret, line[i]);
			if (ret == NULL)
				return (NULL);
		}
		if (count == 0)
			i++;
		else
			count = 0;
	}
	return (ret);
}
